#include <climits>
#include "Instance.h"
#include "../toolBox/Point.h"

#define GENERATE_RANDOM_POINT d(g)

Instance::Instance(int &number_of_shipping,int &mapSize) {
    Instance::m_ID = 0;
    m_shippingPoints.emplace_back(Point(m_depot.getX(),m_depot.getY()),
                                  Point(m_depot.getX(),m_depot.getY()),
                                  m_ID,
                                  "depot",
                                  0,
                                  0,
                                  0
    );
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine g(seed);
    std::uniform_int_distribution<int> d(0,mapSize);
    std::uniform_int_distribution<int> colis(1,2);

    for (int i = 1; i < number_of_shipping+1; i++) {
        m_shippingPoints.emplace_back(Shipping(Point(GENERATE_RANDOM_POINT, GENERATE_RANDOM_POINT),
                                               Point( GENERATE_RANDOM_POINT, GENERATE_RANDOM_POINT),
                                               Instance::m_ID,
                                               std::to_string(i),
                                               5,
                                               5,
                                               colis(g)
        ));
        Instance::m_ID++;
    }
    exportInstances(seed);
}
const Point &Instance::getDepot() const {
    return m_depot;
}

void Instance::setDepot(const Point &Depot) {
    m_depot = Depot;
}

const std::vector<std::vector<double>> &Instance::getDistanceMatrix() const {
    return m_distanceMatrix;
}

void Instance::setDistanceMatrix(const std::vector<std::vector<double>> &DistanceMatrix) {
    m_distanceMatrix = DistanceMatrix;
}

const std::vector<Shipping> &Instance::getShippingPoint() const {
    return m_shippingPoints;
}

void Instance::setShippingPoint(const std::vector<Shipping> &ShippingPoint) {
    m_shippingPoints = ShippingPoint;
}

std::ostream &operator<<(std::ostream &os, const Instance& i) {
    for(const auto& s : i.getShippingPoint()){
        os << s;
    }
    return os;
}

/**
* generate the distance matrix with the depot and shipping points in the Instance class.
*
*/
void Instance::generateDistanceMatrix() {
    std::vector<double> tmp;

    //set distance between the depot and himself which is 0
    tmp.emplace_back(0);

    for(const auto& s : m_shippingPoints){
        if(s.getName()=="depot")continue;
        tmp.emplace_back(Point::distance(m_depot,s.getOrigin()));
        tmp.emplace_back(Point::distance(m_depot,s.getDestination()));
    }
    m_distanceMatrix.emplace_back(tmp);

    for(const auto& s : m_shippingPoints){
        if (s.getName()=="depot")continue;
        m_distanceMatrix.emplace_back(calculateDistance(s,'o'));
        m_distanceMatrix.emplace_back(calculateDistance(s,'d'));
    }
}
/**
* create a list with the distance between a Point and all the others.
*
* @param a Shipping and char to say if we calc for origin or destination.
* @return list of distance as double.
*/

std::vector<double> Instance::calculateDistance(const Shipping& s,char c){
    Point actualPos;
    switch(c){
        case 'o':
            actualPos = s.getOrigin();
            break;
        case 'd':
            actualPos = s.getDestination();
            break;
        default:
            actualPos = Point();
            break;
    }

    std::vector<double> tmp;
    tmp.emplace_back(Point::distance(actualPos,m_depot));

    for(const auto& destinationPoint: m_shippingPoints){
        if (destinationPoint.getName()=="depot")continue;
        tmp.emplace_back(Point::distance(actualPos,destinationPoint.getOrigin()));
        ///if it's the same Shipping and you want to calculate the distance to go from destination to origin you can't.
        if(destinationPoint == s && c =='o'){
            tmp.emplace_back(INT_MAX);
        } else{
            tmp.emplace_back(Point::distance(actualPos,destinationPoint.getDestination()));
        }
    }
    return tmp;
}

void Instance::showDestinationMatrix() {
    for(const auto& i : m_distanceMatrix){
        for(auto j : i){
            std::cout<< std::setw(11) << j << " ; ";
        }
        std::cout << std::endl;
    }
}

void Instance::exportInstances(unsigned seed) {
    std::ofstream file;
    file.open("../instances/" + std::to_string(seed) + ".txt",std::ios::app);
    file << "x:origin, y:origin; x:destination, y:destination\n" ;//x: 32, y:38;x: 56, y:54
    for(const auto& p : m_shippingPoints){
        file << p.getOrigin() << ";" << p.getDestination() << "\n";
    }
    file.close();
}