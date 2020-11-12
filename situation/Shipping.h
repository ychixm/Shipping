#ifndef SHIPPING_SHIPPING_H
#define SHIPPING_SHIPPING_H

#include "../toolBox/Point.h"

class Shipping {
    //TODO : add m^3
private:

    Point m_origin;
    Point m_destination;
    std::string m_name;
    int m_ID;
    bool m_delivered = false;
    double m_volume;
    int m_originWaitingMalus;
    int m_destinationWaitingMalus;


public:
    Shipping(Point a, Point b, int ID, std::string name);
    Shipping(Point &a, Point &b,int ID,std::string &name);
    Shipping(Point &a, Point &b,int ID,std::string &name, int originWaitingMalus, int destinationWaitingMalus, int volume);
    Shipping(Point a, Point b,int ID,std::string name,int originWaitingMalus, int destinationWaitingMalus, int volume);

    const Point &getOrigin() const;

    void setOrigin(const Point &Origin);

    const Point &getDestination() const;

    void setDestination(const Point &Destination);

    const std::string &getName() const;

    void setName(const std::string &Name);

    int getID() const;

    void setID(int ID);

    bool isDelivered() const;

    void delivered();

    void notDelivered();

    double getVolume() const;

    void setVolume(double volume);

    int getOriginWaitingMalus() const;

    void setOriginWaitingMalus(int originWaitingMalus);

    int getDestinationWaitingMalus() const;

    void setDestinationWaitingMalus(int DestinationWaitingMalus);

    friend std::ostream& operator<<(std::ostream& os,const Shipping& s);
    ///the comparison is only on the name of the shipping.
    friend bool operator==(Shipping const& a, Shipping const& b);
};


#endif //SHIPPING_SHIPPING_H
