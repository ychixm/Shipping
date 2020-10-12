#include "Instance.h"
#include "Point.h"

#define GENERATE_RANDOM_POINT  d(g)


Instance::Instance(int &number_of_shipping,int &mapSize) {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine g(seed);
    std::uniform_int_distribution<int> d(0,mapSize);

    for (int i = 1; i < number_of_shipping+1; i++) {
        m_shippingPoints.emplace_back(Shipping(Point(GENERATE_RANDOM_POINT, GENERATE_RANDOM_POINT),
                                               Point( GENERATE_RANDOM_POINT, GENERATE_RANDOM_POINT),
                                               std::to_string(i)
                                              ));
    }
}
const Point &Instance::getDepot() const {
    return m_depot;
}

void Instance::setDepot(const Point &Depot) {
    m_depot = Depot;
}

const std::list<std::list<float>> &Instance::getDistanceMatrix() const {
    return m_distanceMatrix;
}

void Instance::setDistanceMatrix(const std::list<std::list<float>> &DistanceMatrix) {
    m_distanceMatrix = DistanceMatrix;
}

const std::list<Shipping> &Instance::getShippingPoint() const {
    return m_shippingPoints;
}

void Instance::setShippingPoint(const std::list<Shipping> &ShippingPoint) {
    m_shippingPoints = ShippingPoint;
}

std::ostream &operator<<(std::ostream &os, const Instance& i) {
    os <<"depot: "<< i.getDepot() << std::endl;
    for(const auto& s : i.getShippingPoint()){
        os << s;
    }
    return os;
}

/**
* generate the distance matrix with the depot and shipping points in the Instance class
*
*/
void Instance::generateDistanceMatrix() {
    std::list<float> tmp;

    //set distance between the depot and himself which is 0
    tmp.emplace_back(0);

    for(const auto& s : m_shippingPoints){

        tmp.emplace_back(distance(m_depot,s.getOrigin()));
        tmp.emplace_back(distance(m_depot,s.getDestination()));
    }
    m_distanceMatrix.emplace_back(tmp);

    for(const auto& s : m_shippingPoints){

        m_distanceMatrix.emplace_back(calculateDistance(s,'o'));
        m_distanceMatrix.emplace_back(calculateDistance(s,'d'));
        }
}
/**
* create a list with the distance between a Point and all the others
*
* @param
* @return
*/

//TODO : add condition like go from the destination to the origin is useless give "infinite" distance
std::list<float> Instance::calculateDistance(const Shipping& s,char c){
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

    std::list<float> tmp;
    tmp.emplace_back(distance(actualPos,m_depot));

    for(const auto& destinationPoint: m_shippingPoints){
        tmp.emplace_back(distance(actualPos,destinationPoint.getOrigin()));
        tmp.emplace_back(distance(actualPos,destinationPoint.getDestination()));
    }
    return tmp;
}

void Instance::showDestinationMatrix() {
    for(auto i : m_distanceMatrix){
        for(auto j : i){
            std::cout<< std::setw(7) << j << " ; ";
        }
        std::cout << std::endl;
    }
}
