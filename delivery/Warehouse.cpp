#include "Warehouse.h"

Warehouse::Warehouse(std::vector<Shipping> shipPoints,int trucks_number,std::default_random_engine randomEngine)
{
    for(int i = 0; i < trucks_number; i++){
        m_trucks_list.emplace_back(Truck(shipPoints.at(0),i));
    }
    //Truck truck(inst.getShippingPoint().at(0),4000);
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
            //std::cout<< "origine "<< m_deliveryToPlace.at(i).getOrigin() << "; destination " << m_deliveryToPlace.at(i).getDestination() << "; moyenne " << moyenne << std::endl;
            all_distances.push_back(std::pair<double,int>(Point::distance(moyenne,bary),i));
        }
    }
    int index_findLV = smartFindLowestValue(all_distances);
    int index_truck = index_findLV/m_deliveryToPlace.size();//bon camion
    int index_shipping = all_distances.at(index_findLV).second; //on connait alors la bonne commande


    std::cout<<"colis n "<<m_deliveryToPlace.at(index_shipping).getID()<<std::endl;
    //choix des meilleurs spots dans le camion
    double businessTotalDistance = m_businessDistance - m_trucks_list.at(index_truck).getDistance();
    std::cout<<"businessTotalDistance "<<businessTotalDistance<<std::endl;
    std::tuple<int,int,double> originDestination_andDistance = m_trucks_list.at(index_truck).optimize_distance(m_deliveryToPlace.at(index_shipping),m_randomEngine);
    int index_origine = std::get<0>(originDestination_andDistance);
    int index_destination = std::get<1>(originDestination_andDistance);
    double distance_total = std::get<2>(originDestination_andDistance);

    //insertion
    m_businessDistance = businessTotalDistance + distance_total;
    m_trucks_list.at(index_truck).insertInTruck(m_deliveryToPlace.at(index_shipping),index_origine,index_destination,distance_total);
    std::cout<<"index_truck = "<<index_truck<< "; index_origine = "<<index_origine<<"; index_destination = "<<index_destination<<"; total_distance = "<<distance_total<<"; business distance = "<< m_businessDistance<< std::endl;

    //supression de la liste des colis
    auto it = m_deliveryToPlace.begin();
    std::advance(it, index_shipping);
    m_deliveryToPlace.erase(it);
}



void Warehouse::randomInsertion(int truck_id){
    std::uniform_int_distribution<int> distribution(0,m_deliveryToPlace.size()-1);
    int index = distribution(m_randomEngine);//random choice of the shipping we are going to insert
    std::cout<<""<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"colis n "<<m_deliveryToPlace.at(index).getID()<<std::endl;

    std::cout<< test_optimizeDistance(m_deliveryToPlace.at(index),truck_id)<<": truck ok?(1=true/0=false)" <<std::endl;
    // we remove the shipping that we have just inserted in a truck from the list of shipping to insert (m_deliveryToPlace)
    auto it = m_deliveryToPlace.begin();
    std::advance(it, index);
    m_deliveryToPlace.erase(it);
}

bool Warehouse::test_optimizeDistance(Shipping shipping,int truck_id)
{
    std::cout << "truck number: "<< truck_id<<std::endl;
    std::tuple<int,int,double> originDestination_andDistance = m_trucks_list.at(truck_id).optimize_distance(shipping,m_randomEngine);
    int index_origine = std::get<0>(originDestination_andDistance);
    int index_destination = std::get<1>(originDestination_andDistance);
    double distance_total = std::get<2>(originDestination_andDistance);

    m_businessDistance += distance_total;
    std::cout<<"id_truck = "<<truck_id<< "; index_origine = "<<index_origine<<"; index_destination = "<<index_destination<<"; total_distance = "<<distance_total<<"; business distance = "<< m_businessDistance<< std::endl;

    if(m_trucks_list.at(truck_id).getSteps().size() == 2){//il n'y avait que le dépot
        m_numberOfTrucksStarted ++;
        std::cout<<"m_numberOfTrucksStarted = "<<m_numberOfTrucksStarted<<std::endl;
    }
    return m_trucks_list.at(truck_id).insertInTruck(shipping,index_origine,index_destination,distance_total);

}

/*int Warehouse::randomFindLowestValue(std::vector<double> tab) {
    int value = INT_MAX;
    int index = 0;
    std::cout<<""<<std::endl;
    //std::cout<< "tab size: "<< tab.size()<<std::endl;
    for(int i = 4; i < tab.size(); i+= 5){
        //std::cout<<"tab[i]:  "<<tab[i]<<std::endl;
        if(tab[i] < value){
            value = tab[i];
            index = i;
        }
    }
    std::cout<< "m_businessDistance: " << m_businessDistance <<std::endl;
    return (index-4);
}*/

int Warehouse::smartFindLowestValue(std::vector<std::pair<double,int>> tab) {
    int value = INT_MAX;
    int index = 0;
    std::cout<<""<<std::endl;
    //std::cout<< "tab size: "<< tab.size()<<std::endl;
    for(int i = 0; i < tab.size(); i++){
        //std::cout<<"tab[i]:  "<<tab[i].first<<std::endl;
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
