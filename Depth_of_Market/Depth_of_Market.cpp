
#include <iostream>
#include <memory>
#include <map>


//Придумать или выбрать способ сортровки заказов в стакане на основании цены, чтобы для вывода топ 10 лучших, выводить this->Orders(0..9)

enum changeOrderRetvalType {
    invalidUUID = 0,
    success,
    invalidCost,
    invalidQuantity,
    prev_is_equal
};

class DOF {


    DOF() = default;

    ~DOF() = default;

public:
    typedef uint16_t orderIDtype;
    typedef std::pair<float, float> orderType;
    typedef std::map<orderIDtype, orderType> ordersType;

    orderIDtype addOrder(float cost, float quantity);
    changeOrderRetvalType changeOrder(orderIDtype order, float cost, float quantity);
    void deleteOrder(orderIDtype order);
    ordersType ShowTopOrders();


private:
    static orderIDtype curUUID;
    ordersType Orders;
    ordersType BestOrders;
};

DOF::orderIDtype DOF::addOrder(float cost, float quantity)
{
    if(!cost || !quantity) return 0;
    curUUID++;
    Orders.emplace(curUUID, std::make_pair(cost, quantity));
    return curUUID;
}

changeOrderRetvalType DOF::changeOrder(orderIDtype order, float cost, float quantity)
{
    changeOrderRetvalType retval;

    auto itr_Order = Orders.find(order);

    if (itr_Order == Orders.end()) return changeOrderRetvalType::invalidUUID;
    if (!cost) return changeOrderRetvalType::invalidCost;
    if (!quantity) return changeOrderRetvalType::invalidQuantity;

    auto OrderInDOF = itr_Order->second;

    if (OrderInDOF.first == cost || OrderInDOF.second == quantity)  return changeOrderRetvalType::prev_is_equal;
    
    OrderInDOF = std::make_pair(cost, quantity);
    return changeOrderRetvalType::success;
}

void DOF::deleteOrder(orderIDtype order)
{
    auto itr_Order = Orders.find(order);
    if (itr_Order != Orders.end())
        Orders.erase(order);
}

DOF::ordersType DOF::ShowTopOrders()
{
    BestOrders;
    return ordersType();
}



int main()
{
    std::shared_ptr<DOF> pDOF;


}

