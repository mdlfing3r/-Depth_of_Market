
#include <iostream>
#include <memory>
#include <map>


//Придумать или выбрать способ сортровки заказов в стакане на основании цены, чтобы для вывода топ 10 лучших, выводить this->Orders(0..9)
//Может для офера стоит использовать структуру ?
enum editOrderRetval_t {
    invalidUUID = 0,
    success,
    invalidCost,
    invalidQuantity,
    prev_is_equal
};

enum operation_t {
    sell = 0,
    buy
};

class DOF {

    DOF() = default;

    ~DOF() = default;

public:
    typedef uint16_t offerID_t;
    typedef std::pair<float, float> offer_t;
    typedef std::pair<offerID_t, offer_t> transaction_t;
    typedef <transaction_t>;

    offerID_t createOrder(offer_t offerParams, operation_t operationType);
    editOrderRetval_t editOrder(transaction_t transaction);
    offerID_t ShowTopOrders();
    void deleteOrder(offerID_t order);


private:
    offerID_t createSellOrder(offer_t offerParams);
    offerID_t createBuyOrder(offer_t offerParams);
    static offerID_t curUUID;
    transaction_t Orders;
    transaction_t BestOrders;
};

DOF::offerID_t DOF::createOrder(offer_t offerParams, operation_t operationType)
{
    if(!offerParams.first || !offerParams.second) return 0;
    curUUID++;

    switch (operationType) {
        case operation_t::sell:
            createSellOrder(offerParams);
            break;
        case operation_t::buy:
            createBuyOrder(offerParams);
            break;
        default:
            break;
    }

    Orders.emplace(curUUID, offerParams);
    return curUUID;
}

editOrderRetval_t DOF::editOrder(transaction_t transaction)
{
    editOrderRetval_t retval;

    auto itr_Order = Orders.find(transaction);

    if (itr_Order == Orders.end()) return editOrderRetval_t::invalidUUID;
    if (!cost) return editOrderRetval_t::invalidCost;
    if (!quantity) return editOrderRetval_t::invalidQuantity;

    auto OrderInDOF = itr_Order->second;

    if (OrderInDOF.first == cost || OrderInDOF.second == quantity)  return editOrderRetval_t::prev_is_equal;
    
    OrderInDOF = std::make_pair(cost, quantity);
    return editOrderRetval_t::success;
}

void DOF::deleteOrder(orderID_t order)
{
    auto itr_Order = Orders.find(order);
    if (itr_Order != Orders.end())
        Orders.erase(order);
}

DOF::orderID_t DOF::ShowTopOrders()
{
    BestOrders;
    return ordersType();
}



int main()
{
    std::shared_ptr<DOF> pDOF;


}

