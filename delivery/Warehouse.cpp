#include <climits>
#include "Warehouse.h"

Warehouse::Warehouse(std::vector<Shipping> shipPoints,int trucks_number)
{
    std::vector<Truck> m_truks_list = std::vector<Truck>();
    for(int i = 0; i < trucks_number; i++){
        m_trucks_list.emplace_back(shipPoints.at(0),1500);
    }
    //Truck truck(inst.getShippingPoint().at(0),4000);
    std::copy(++shipPoints.begin(),shipPoints.end(),std::back_inserter(m_deliveryToPlace));
    //we copy the list of shipping in order to remove a shipping after inserting it in a truck
    m_businessDistance = 0;
}


void Warehouse::optimizeInsertion(){

    while(!m_deliveryToPlace.empty()){
        int index = rand()%m_deliveryToPlace.size();//random choice of the shipping we are going to insert
        std::cout<<""<<std::endl;
        std::cout<<""<<std::endl;
        std::cout<<"colis n°"<<m_deliveryToPlace.at(index).getID()<<std::endl;

        std::cout<< test_optimizeDistance(m_deliveryToPlace.at(index))<<": truck ok?(1=true/0=false)" <<std::endl;
        // we remove the shipping that we have just inserted in a truck from the list of shipping to insert (m_deliveryToPlace)
        auto it = m_deliveryToPlace.begin();
        std::advance(it, index);
        m_deliveryToPlace.erase(it);
    }
}

bool Warehouse::test_optimizeDistance(const Shipping& shipping)
{
    std::vector<double> all_trucks = std::vector<double>();
    double businessTotalDistance = m_businessDistance;
    for(int i = 0; i < m_trucks_list.size();i++){
        std::cout<<""<<std::endl;
        std::cout<<""<<std::endl;
        std::cout << "truck number: "<< i<<std::endl;
        std::cout<< "total business distance: " << businessTotalDistance<<std::endl;
        businessTotalDistance -= m_trucks_list.at(i).getDistance();
        std::tuple<int,int,double> originDestination_andDistance = m_trucks_list.at(i).optimize_distance(shipping);
        int index_origine = std::get<0>(originDestination_andDistance);
        int index_destination = std::get<1>(originDestination_andDistance);
        double distance_total = std::get<2>(originDestination_andDistance);
        std::cout << "Warehouse index de l'origine: "<< index_origine <<std::endl;
        all_trucks.push_back(i);
        all_trucks.push_back(index_origine);
        all_trucks.push_back(index_destination);
        all_trucks.push_back(distance_total);
        all_trucks.push_back(distance_total + businessTotalDistance);
        businessTotalDistance = m_businessDistance;
    }
    int index_findLowestValue = findLowestValue(all_trucks);
    int id_truck = (int)all_trucks.at(index_findLowestValue);
    m_businessDistance = all_trucks.at(index_findLowestValue+3);
    return m_trucks_list.at(id_truck).insertInTruck(shipping,all_trucks.at(index_findLowestValue+1),all_trucks.at(index_findLowestValue+2),all_trucks.at(index_findLowestValue+3));

}

int Warehouse::findLowestValue(std::vector<double> tab) {
    int value = INT_MAX;
    int index = 0;
    std::cout<< "tab size: "<< tab.size()/4<<std::endl;
    for(int i = 4; i < tab.size(); i+= 5){
        std::cout<<"tab[i]:  "<<tab[i]<<std::endl;
        if(tab[i] < value){
            value = tab[i];
            index = i;
        }
    }
    m_businessDistance = value;
    std::cout<< "m_businessDistance: " << m_businessDistance <<std::endl;
    return (index-4);
}