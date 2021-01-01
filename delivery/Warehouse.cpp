#include "Warehouse.h"

Warehouse::Warehouse(std::vector<Shipping> shipPoints,int trucks_number,std::default_random_engine randomEngine)
{
    for(int i = 0; i < trucks_number; i++){
        m_trucks_list.emplace_back(Truck(shipPoints.at(0),i));
    }
    std::copy(++shipPoints.begin(),shipPoints.end(),std::back_inserter(m_deliveryToPlace));
    //we copy the list of shipping in order to remove a shipping after inserting it in a truck
    m_businessDistance = 0;
    m_randomEngine = randomEngine;
    m_numberOfTrucksStarted = 0;

}

std::vector<Truck> Warehouse:: getTrucks_list(){
    return m_trucks_list;
}

void Warehouse::switchInsertion(){
    while(!m_deliveryToPlace.empty()){
        //si chaque camion a commencé à être rempli
        if(m_numberOfTrucksStarted == m_trucks_list.size()){
            smartInsertion();
        }
            //sinon remplissage aléatoire pour intialiser chaque camion
        else{
            randomInsertion(m_numberOfTrucksStarted);
        }
    }
}

void Warehouse::smartInsertion(){
    std::vector<Point> barycentre = std::vector<Point>();
    std::vector<std::pair<double,int>>all_distances = std::vector<std::pair<double,int>>();

    //création des barycentre
    for(Truck truck: m_trucks_list){
        barycentre.push_back(truck.getBarycentre());
    }
    //calcul des distances entre chaque colis et chaque barycentre
    for(Point bary: barycentre){
        for(int i = 0 ; i < m_deliveryToPlace.size() ; i++){
            Point moyenne((m_deliveryToPlace.at(i).getOrigin().getX() + m_deliveryToPlace.at(i).getDestination().getX())/2,(m_deliveryToPlace.at(i).getOrigin().getY() + m_deliveryToPlace.at(i).getDestination().getY())/2);
            all_distances.emplace_back(Point::distance(moyenne,bary),i);
        }
    }
    int index_findLV = smartFindLowestValue(all_distances);
    int index_truck = int(index_findLV/m_deliveryToPlace.size());//bon camion
    int index_shipping = all_distances.at(index_findLV).second; //on connait alors la bonne commande


    //choix des meilleurs spots dans le camion
    double businessTotalDistance = m_businessDistance - m_trucks_list.at(index_truck).getDistance();
    std::tuple<int,int,double> originDestination_andDistance = m_trucks_list.at(index_truck).optimize_distance(m_deliveryToPlace.at(index_shipping),m_randomEngine);
    int indexOrigin = std::get<0>(originDestination_andDistance);
    int index_destination = std::get<1>(originDestination_andDistance);
    double distance_total = std::get<2>(originDestination_andDistance);

    //insertion
    m_businessDistance = businessTotalDistance + distance_total;
    m_trucks_list.at(index_truck).insertInTruck(m_deliveryToPlace.at(index_shipping), indexOrigin, index_destination, distance_total);

    //supression de la liste des colis
    auto it = m_deliveryToPlace.begin();
    std::advance(it, index_shipping);
    m_deliveryToPlace.erase(it);
}



void Warehouse::randomInsertion(int truck_id){
    std::uniform_int_distribution<int> distribution(0,m_deliveryToPlace.size()-1);
    int index = distribution(m_randomEngine);//random choice of the shipping we are going to insert
    test_optimizeDistance(m_deliveryToPlace.at(index),truck_id);
    // we remove the shipping that we have just inserted in a truck from the list of shipping to insert (m_deliveryToPlace)
    auto it = m_deliveryToPlace.begin();
    std::advance(it, index);
    m_deliveryToPlace.erase(it);
}

bool Warehouse::test_optimizeDistance(const Shipping& shipping,int truck_id)
{
    std::tuple<int,int,double> originDestinationAndDistance = m_trucks_list.at(truck_id).optimize_distance(shipping, m_randomEngine);
    int indexOrigin = std::get<0>(originDestinationAndDistance);
    int indexDestination = std::get<1>(originDestinationAndDistance);
    double distanceTotal = std::get<2>(originDestinationAndDistance);

    m_businessDistance += distanceTotal;


    if(m_trucks_list.at(truck_id).getSteps().size() == 2){//il n'y avait que le dépot
        m_numberOfTrucksStarted ++;
    }
    return m_trucks_list.at(truck_id).insertInTruck(shipping, indexOrigin, indexDestination, distanceTotal);

}

int Warehouse::smartFindLowestValue(std::vector<std::pair<double,int>> tab) {
    int value = INT_MAX;
    int index = 0;
    for(int i = 0; i < tab.size(); i++){
        if(tab[i].first < value){
            value = tab[i].first;
            index = i;
        }
    }
    return (index);
}



double Warehouse::getBusinessDistance() const {
    return m_businessDistance;
}

std::ostream& operator<<(std::ostream& os, Warehouse w){
    os << w.getBusinessDistance();
    return os;
}

Warehouse::Warehouse(){}

void Warehouse::exportPath(unsigned seed) {
    std::ofstream file;
    std::string name = std::to_string(this->getBusinessDistance())+ "-" + std::to_string(seed);

    file.open("../results/" + name +".txt",std::ios::app);
    for(const auto& t : m_trucks_list){
        file << "truck:" << t.getID() << ":";
        for(const auto& e : t.getSteps()){
            if(e.second){
                file << e.first.getName()+" o" + "," << e.first.getOrigin().getX() << "," << e.first.getOrigin().getY() << ":";
            }
            else{
                file << e.first.getName()+" d" + "," << e.first.getDestination().getX() << "," << e.first.getDestination().getY() << ":";
            }
        }
        file << "\n" ;
    }
    file << double(m_businessDistance) << ":" << unsigned(seed);
    file.close();
}
