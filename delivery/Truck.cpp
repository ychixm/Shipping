#include "Truck.h"
#include "../situation/Instance.h"
#include <climits>

std::vector<std::vector<float> > Truck::Matrix = std::vector<std::vector<float> >();

Truck::Truck(Shipping shipping, float distance):m_distance(distance){
    m_steps.insert(m_steps.begin(),1,std::pair<Shipping,bool>(shipping,false));
    m_steps.insert(m_steps.begin(),1,std::pair<Shipping,bool>(shipping,true));
    m_distance = 0;
}

int Truck::getID() const {
    return m_ID;
}

void Truck::setID(int ID) {
    m_ID = ID;
}

float Truck::getDistance() const {
    return m_distance;
}

void Truck::setDistance(float distance) {
    Truck::m_distance = distance;
}

const std::list<std::pair<Shipping,bool> > &Truck::getSteps() const {
    return m_steps;
}

void Truck::setSteps(const std::list<std::pair<Shipping,bool> > &steps) {
    Truck::m_steps = steps;
}

float Truck::getCapacity() const {
    return m_capacity;
}

void Truck::setCapacity(float capacity) {
    m_capacity = capacity;
}


// this function return a copy of the truck route and insert a point in this copy at the desired index

std::list<std::pair<Shipping, bool> > Truck::updatedListCopy(std::list<std::pair<Shipping, bool> > steps, int index, const Shipping& ship, bool origin) {
    std::list<std::pair<Shipping, bool> > tmp;
    std::copy(steps.begin(), steps.end(), std::back_inserter(tmp));
    auto it = tmp.begin();
    std::advance(it, index);
    tmp.insert(it,1,std::pair<Shipping, bool>(ship,origin));
    std::cout<<"taille liste: "<<tmp.size()<<std::endl;
    return tmp;
}


//this function return if a truck can accepts a shipping and if it's the case, it adds the shipping on the truck route

std::tuple<int,int,double> Truck::optimize_distance(Shipping shipping){

    std::cout<<"entree de l'origine"<<std::endl;
    std::cout<<""<<std::endl;
    std::pair<int,double> best_origin = findBestSpot(shipping,1,true);
    int index_origin = best_origin.first;
    std::cout<<"index_origine :"<<index_origin<<std::endl;

    std::cout<<""<<std::endl;
    std::cout<<"entree de destination"<<std::endl;
    std::pair<int,double> best_destination = findBestSpot(shipping,index_origin+1,false);
    int index_destination = best_destination.first;
    double distance_totale = best_destination.second;
    std::cout<<"index_destination :"<<index_destination<<std::endl;

    std::tuple<int,int,double> oriDestDist(index_origin,index_destination,distance_totale);
    return oriDestDist;
}

bool Truck::insertInTruck(Shipping shipping,double origin,double destination,double distance){
    auto it = m_steps.begin();
    int index_origin = (int)origin;
    if (index_origin > 0) {
        std::advance(it,index_origin);
        m_steps.insert(it,1,std::pair<Shipping, bool>(shipping,true));
    }
    else{
        return false;
    }

    auto it_dest = m_steps.begin();
    int index_destination = (int)destination;
    if (index_destination > 0){
        std::advance(it_dest,index_destination);
        m_steps.insert(it,1,std::pair<Shipping, bool>(shipping,false));
        return(true);
    }
    else{
        return false;
    }
    m_distance = distance;

}



//this function takes a shipping point(origin if origin==true, destination...) and the first index where we can insert it
//she return the best spot of to insert the point

std::pair<int,double> Truck::findBestSpot(Shipping shipping, int start , bool origin){
    std::vector<double> distance_list(start,INT_MAX);
    std::list<std::pair<Shipping,bool>> tableau_origin = m_steps;//ce tableau permet d'adapter le for qui suit selon si on a une origine ou une destination à inserer
    if(!origin){
        tableau_origin = Truck::updatedListCopy(m_steps,start-1,shipping,true);
    }
    for(int index = start ; index < tableau_origin.size() ; index++){
        std::list<std::pair<Shipping,bool>> tableau_copie = Truck::updatedListCopy(tableau_origin,index,shipping,origin);
        auto it_distance = tableau_copie.begin();
        double distance_totale = 0;
        m_capacity = INITIAL_CAPACITY;
        for(it_distance = tableau_copie.begin(); it_distance != --tableau_copie.end() ; it_distance ++){
            /*if (it_distance->second) {//if it is an origin we withdraw the volume of the shipping to the truck
                Truck::setCapacity(Truck::getCapacity - it_distance->first.getVolume());
                std::cout<<"origin"<<std::endl;
            }*/
            if (it_distance->second) {//if it is an origin we withdraw the volume of the shipping to the truck
                m_capacity -= (it_distance)->first.getVolume();
            }
            else{//if it is an destination we add the volume of the shipping to the truck
                m_capacity += it_distance->first.getVolume();
            }
            if(m_capacity >= 0){
                distance_totale += Truck::distanceWithMalus(*it_distance,*std::next(it_distance,1));
            }
            else{
                distance_totale = INT_MAX;
            }
        }
        std::cout<<"passage n°"<<index-start<<" distance totale :"<< distance_totale<<std::endl;
        distance_list.push_back(distance_totale);
        //we currently have an array: distance_list containing the distance for each index between the two depots in the truck route
        //now we find the index of the minimum total distance
    }
    return findLowestDistance_andValue(distance_list);
}

/*int Truck::findLowestValue(std::vector<double> tab) {
    int value = INT_MAX;
    int index = 0;
    for(int i = 0; i < tab.size(); i++){
        std::cout<<tab[i]<<std::endl;
        if(tab[i] < value){
            value = tab[i];
            index = i;
        }
    }
    return index;
}*/

std::pair<int,double> Truck::findLowestDistance_andValue(std::vector<double> tab) {
    int value = INT_MAX;
    int index = 0;
    for(int i = 0; i < tab.size(); i++){
        std::cout<<tab[i]<<std::endl;
        if(tab[i] < value){
            value = tab[i];
            index = i;
        }
    }
    return {index,value};
}

double Truck::distanceWithMalus(const std::pair<Shipping, bool>& a, const std::pair<Shipping, bool>& b) {
    if (a.second && b.second){
        int A = (a.first.getID()*2)+1;
        int B = (b.first.getID()*2)+1;
        if(a.first.getName() == "depot"){
            A = 0;
        }
        if(b.first.getName() == "depot"){
            B = 0;
        }
        return Truck::Matrix.at(B).at(A) + double(a.first.getOriginWaitingMalus());
        //return Point::distance(a.first.getOrigin(),b.first.getOrigin()) + a.first.getOriginWaitingMalus();
    }
    else if (a.second && !b.second){
        int A = (a.first.getID()*2)+1;
        int B = (b.first.getID()*2)+2;
        if(a.first.getName() == "depot"){
            A = 0;
        }
        if(b.first.getName() == "depot"){
            B = 0;
        }
        return Truck::Matrix.at(B).at(A) + double(a.first.getOriginWaitingMalus());

        //return Point::distance(a.first.getOrigin(),b.first.getDestination())+ a.first.getOriginWaitingMalus();
    }
    else if (!a.second && b.second){
        int A = (a.first.getID()*2)+2;
        int B = (b.first.getID()*2)+1;
        if(a.first.getName() == "depot"){
            A = 0;
        }
        if(b.first.getName() == "depot"){
            B = 0;
        }
        return Truck::Matrix.at(B).at(A) + double(a.first.getDestinationWaitingMalus());

        //return Point::distance(a.first.getDestination(),b.first.getOrigin())+ a.first.getDestinationWaitingMalus();
    }
    else if (!a.second && !b.second){
        int A = (a.first.getID()*2)+2;
        int B = (b.first.getID()*2)+2;
        if(a.first.getName() == "depot"){
            A = 0;
        }
        if(b.first.getName() == "depot"){
            B = 0;
        }
        return Truck::Matrix.at(B).at(A)+ double(a.first.getDestinationWaitingMalus());

        //return Point::distance(a.first.getDestination(),b.first.getDestination())+ a.first.getDestinationWaitingMalus();
    }
}

void Truck::exportSteps(){
    std::ofstream file;
    file.open("../instances/data.txt",std::ios::app);
    file << "truck:" << m_ID << ":";
    for(const auto& e : m_steps){
        if(e.second){
            file << e.first.getName()+" o" + "," << e.first.getOrigin().getX() << "," << e.first.getOrigin().getY() << ":";
        }
        else{
            file << e.first.getName()+" d" + "," << e.first.getDestination().getX() << "," << e.first.getDestination().getY() << ":";
        }
    }
    file << "\n" ;
    file.close();
}
