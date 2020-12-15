#include "Truck.h"
#include <climits>

std::mutex Truckmtx;
std::vector<std::vector<float> > Truck::Matrix = std::vector<std::vector<float> >();

Truck::Truck(Shipping shipping,int id){
    m_steps.insert(m_steps.begin(),1,std::pair<Shipping,bool>(shipping,false));
    m_steps.insert(m_steps.begin(),1,std::pair<Shipping,bool>(shipping,true));
    m_distance = 0;
    m_ID = id;
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

std::default_random_engine Truck::randomEngine;

// this function return a copy of the truck route and insert a point in this copy at the desired index

std::list<std::pair<Shipping, bool> > Truck::updatedListCopy(std::list<std::pair<Shipping, bool> > steps, int index, const Shipping& ship, bool origin) {
    std::list<std::pair<Shipping, bool> > tmp;
    std::copy(steps.begin(), steps.end(), std::back_inserter(tmp));
    auto it = tmp.begin();
    std::advance(it, index);
    tmp.insert(it,1,std::pair<Shipping, bool>(ship,origin));
    return tmp;
}


//this function return if a truck can accepts a shipping and if it's the case, it adds the shipping on the truck route

std::tuple<int,int,double> Truck::optimize_distance(Shipping shipping,std::default_random_engine randomEngine){

    std::pair<int,double> best_origin = findBestSpot(shipping,1,true,randomEngine);
    int index_origin = best_origin.first;

    std::pair<int,double> best_destination = findBestSpot(shipping,index_origin+1,false,randomEngine);
    int index_destination = best_destination.first;
    double distance_totale = best_destination.second;

    std::tuple<int,int,double> oriDestDist(index_origin,index_destination,distance_totale);
    return oriDestDist;
}

//cette fonction permet d'ajouter un colis dans ce camion
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
        m_distance = distance;
        return(true);
    }
    else{
        return false;
    }


}



//this function takes a shipping point(origin if origin==true, destination...) and the first index where we can insert it
//she return the best spot of to insert the point

std::pair<int,double> Truck::findBestSpot(Shipping shipping, int start , bool origin,std::default_random_engine randomEngine){
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
        distance_list.push_back(distance_totale);
        //we currently have an array: distance_list containing the distance for each index between the two depots in the truck route
        //now we find the index of the minimum total distance
    }
    return randomLowestValue(distance_list,randomEngine);
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
        if(tab[i] < value){
            value = tab[i];
            index = i;
        }
    }
    return std::pair<int,double>(index,value);
}

std::pair<int,double>Truck::randomLowestValue(std::vector<double> tab,std::default_random_engine randomEngine){
    std::vector<std::pair<int,double>> lowestValues;
    for(int i = 0; i < tab.size(); i++){
        if(tab[i] < INT_MAX){
            lowestValues.push_back(std::pair<int,double>(i,tab[i]));
            //si la distance est éligible alors on l'ajoute au tableau
        }
    }
    //on trie le tableau lowestValues par ordre croissant de distance

    std::sort(lowestValues.begin(), lowestValues.end(), [] (const std::pair<int,double> &pair1, const std::pair<int,double> &pair2) {
        return pair1.second < pair2.second;
    });
    //la boucle for qui suit permet de vérifier que le tri a réussi
    /*for (const auto &pair : lowestValues) {
        std::cout <<"pouuuuuuu" << pair.first << " = " << pair.second << std::endl;
    }*/
    //on tire parmi les 4 meilleurs résultats si il existe
    int choice;
    if(lowestValues.size()>3){
        std::uniform_int_distribution<int> distribution(0,3);
        return lowestValues[distribution(randomEngine)];
    }
    else{
        std::uniform_int_distribution<int> distribution(0,lowestValues.size()-1);
        return lowestValues[distribution(randomEngine)];
    }

}

Point Truck::getBarycentre(){
    Point Barycentre;
    double X = 0;
    double Y = 0;
    for(auto it_shipping = ++m_steps.begin(); it_shipping != --m_steps.end(); it_shipping ++){//on ne veut compter qu'une fois le dépot (déjà fait dans l'initialisation)
        if(it_shipping->second){
            X = (it_shipping)->first.getOrigin().getX();
            Y = it_shipping->first.getOrigin().getY();
        }
        else{
            X = it_shipping->first.getDestination().getX();
            Y = it_shipping->first.getDestination().getY();
        }
    }
    return Point(int(X/(m_steps.size()-1)),int(Y/(m_steps.size()-1)));
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
        Truckmtx.lock();
        double tmp = Truck::Matrix.at(B).at(A) + double(a.first.getOriginWaitingMalus());
        Truckmtx.unlock();
        return tmp;
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
        Truckmtx.lock();
        double tmp = Truck::Matrix.at(B).at(A) + double(a.first.getOriginWaitingMalus());
        Truckmtx.unlock();
        return tmp;

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
        Truckmtx.lock();
        double tmp = Truck::Matrix.at(B).at(A) + double(a.first.getDestinationWaitingMalus());
        Truckmtx.unlock();
        return tmp;

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
        Truckmtx.lock();
        double tmp = Truck::Matrix.at(B).at(A)+ double(a.first.getDestinationWaitingMalus());
        Truckmtx.unlock();
        return tmp;

        //return Point::distance(a.first.getDestination(),b.first.getDestination())+ a.first.getDestinationWaitingMalus();
    }
}

void Truck::exportSteps(){
    std::ofstream file;
    file.open("C:/Users/nicol/Documents/4ème année/projetCplus_plus/data.txt",std::ios::app);
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