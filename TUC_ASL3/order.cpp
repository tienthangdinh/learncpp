#include <string>
#include <utility>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

class Order {
    private:
    int id;
    std::string description;
    int priority;
    int arrivalTime;
    int executionTime;

    public:
    Order(int id, std::string description, int priority, int arrivalTime, int executionTime)
    : id(id), description(std::move(description)), priority(priority), arrivalTime(arrivalTime), executionTime(executionTime) {

    }
    int getID() const {
        return id;
    }
    std::string getDescription() const {
        return description;
    }
    int getArrivalTime() const {
        return arrivalTime;
    }
    int getExecutionTime() const {
        return executionTime;
    }
    int getPriority() const {
        return priority;
    }
};



class Node {
    private:
    Order data;
    Node* next;
    Node* prev;

    public:
    Node(Order order) : data(order), prev(nullptr), next(nullptr) {}

    Order getData() const {
        return data;
    }
    Node* getNext() {
        return this->next;
    }
    Node* getPrev() {
        return this->prev;
    }
    void setNext(Node* nextNode) {
        this->next = nextNode;
    }
    void setPrev(Node* prevNode) {
        this->prev = prevNode;
    }
};







class List {
    private:
    Node* head;

    Node* getNodeAt(int index) {
        if (index < 0 || !head) return nullptr;
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->getNext();
            if (!current) return nullptr;
        }
        return current;
    }
    public:
    List() : head(nullptr) {}
    ~List() {
        Node* current = head;
        while (current) {
            Node* next = current->getNext();
            delete current;
            current = next;
        }
    }
    Node* getHead() {
        return this->head;
    }

    bool append(Node* node) {
        if (!node) return false;
        node->setNext(nullptr);
        node->setPrev(nullptr);
        if (!head) {
            this->head = node;
            return true;
        }
        Node* current = head;
        while (current->getNext()) {
            current = current->getNext();
        }
        current->setNext(node);
        node->setPrev(current);
        return true;
    }

    bool insert(int index, Node* node) {
        if (!node || index < 0) return false;
        if (index == 0) {
            node->setNext(this->head);
            node->setPrev(nullptr);
            if (this->head) {
                this->head->setPrev(node);
            }
            this->head = node;
            return true;
        } 
        Node* current = getNodeAt(index);
        if (!current) {
            //check if appending to the absolute end
            Node* last = head;
            int count = 0;
            while (last && last->getNext()) {
                last = last->getNext();
                count+=1;
            }
            if (index == count + 1 && last) {
                return append(node);
            }
            return false;
        }
        Node* prev = current->getPrev();
        node->setNext(current);
        node->setPrev(prev);
        if (prev) { //always check if it even exists
            prev->setNext(node);
        }
        current->setPrev(node);
        return true;
    }

    bool remove(int index) {
        Node* target = getNodeAt(index);
        if (!target) return false;
        Node* previous = target->getPrev();
        Node* next = target->getNext();
        
        if (target == head) {
            head = next;
        }
        else {
            previous->setNext(next);
        }
        
        if (next) {
            next->setPrev(previous);
        }
        delete target;
        return true;
    }

    bool swap(int firstIndex, int secondIndex) {
        if (firstIndex == secondIndex) return true;

        Node* node1 = getNodeAt(firstIndex);
        Node* node2 = getNodeAt(secondIndex);

        if (!node1 || !node2) return false;

        if (firstIndex > secondIndex) std::swap(node1, node2);

        Node* p1 = node1->getPrev();
        Node* n1 = node1->getNext();
        Node* p2 = node2->getPrev();
        Node* n2 = node2->getNext();

        if (n1 == node2) {
            node2->setPrev(p1);
            node2->setNext(node1);
            node1->setPrev(node2);
            node1->setNext(n2);
            if (n2) n2->setPrev(node1);
            if (p1) p1->setNext(node2);
        } else {
            node1->setNext(n2);
            node1->setPrev(p2);
            node2->setNext(n1);
            node2->setPrev(p1);
            if (p1) p1->setNext(node2);
            if (n1) n1->setPrev(node2);
            if (p2) p2->setNext(node1);
            if (n2) n2->setPrev(node1);
        }
        if (head == node1) head = node2;
        else if (head == node2) head = node1;
        return true;
    }

    void sort() {
        if (!head || head->getNext()) return;
        //get the length
        int length=0;
        Node* curr = head;
        while (curr) {
            curr = curr->getNext();
            length++;
        }

        for (int i = 0; i < length ; ++i) {
            for (int j = 0; j < length - i - 1; ++j) {
                //compare j and j+1
                Node* nodej = getNodeAt(j);
                Node* nextnode = (nodej) ? nodej->getNext() : nullptr;
                if (nodej && nextnode) {
                    if (nodej->getData().getPriority() < nextnode->getData().getPriority()) {
                        swap(j, j+1);
                    }
                }
            }
        }
    }


    Order pollMostUrgentOrder() {
        if (!head) throw std::runtime_error("List empty");

        //just simply iterate over to get the best
        int highest_prio = -1;
        int highest_prio_id = -1;

        Node* curr = head;
        int idx = 0;

        while (curr) {
            int current_prio = curr->getData().getPriority();
            if (current_prio > highest_prio) {
                highest_prio = current_prio;
                highest_prio_id = idx;
            }
            curr = curr->getNext();
            idx++;
        }

        Node* target_node = getNodeAt(highest_prio_id);
        Order target_order = target_node->getData();

        remove(highest_prio_id);
        return target_order;
    }
};


//this part was generated by Gemini because im sleep and dont have time
class Restaurant {
private:
    int executionUnits;
    List order_list; // Uses our custom List class handling dynamic memory node paths

public:
    Restaurant(int executionUnits) : executionUnits(executionUnits) {}

    bool addOrder(int id, std::string description, int priority, int arrivalTime, int executionTime) {
        Node* current = order_list.getHead();
        while (current) {
            if (current->getData().getID() == id) {
                return false;
            }
            current = current->getNext();
        }

        Order new_order(id, description, priority, arrivalTime, executionTime);
        Node* new_node = new Node(new_order);
        return order_list.append(new_node);
    }

    bool removeOrder(int id) {
        Node* current = order_list.getHead();
        int idx = 0;
        while (current) {
            if (current->getData().getID() == id) {
                return order_list.remove(idx);
            }
            current = current->getNext();
            idx++;
        }
        return false;
    }

    // Returns empty vector pointer simulation wrapper matching Java's 'null' condition safely
    std::vector<std::string>* displayKMostUrgentOrders(int k) {
        int size = 0;
        Node* current = order_list.getHead();
        while (current) {
            size++;
            current = current->getNext();
        }

        if (k > size) return nullptr;

        order_list.sort();

        auto* result = new std::vector<std::string>();
        current = order_list.getHead();
        for (int i = 0; i < k; ++i) {
            if (current) {
                Order o = current->getData();
                result->push_back(std::to_string(o.getID()) + ", " + o.getDescription() + ", " + std::to_string(o.getPriority()));
                current = current->getNext();
            }
        }
        return result;
    }

    std::vector<std::vector<std::string>> execute() {
        std::vector<std::vector<std::string>> result_log;

        // Vector tracking runtime execution blocks
        struct ChefStatus {
            bool working = false;
            Order* active_order = nullptr;
            int time_left = 0;
        };

        std::vector<ChefStatus> units(executionUnits);
        int current_time = 0;

        while (true) {
            bool has_pending_orders = (order_list.getHead() != nullptr);
            bool has_active_work = false;

            for (int i = 0; i < executionUnits; ++i) {
                if (units[i].working) {
                    units[i].time_left--;
                    if (units[i].time_left == 0) {
                        units[i].working = false;
                        delete units[i].active_order; // Memory cleanup for copy allocations
                        units[i].active_order = nullptr;
                    } else {
                        has_active_work = true;
                    }
                }
            }

            if (!has_pending_orders && !has_active_work) {
                break;
            }

            // Assign free units to highest-priority valid tasks
            for (int i = 0; i < executionUnits; ++i) {
                if (!units[i].working) {
                    int best_node_idx = -1;
                    int best_priority = -1;
                    Node* best_node = nullptr;

                    Node* curr = order_list.getHead();
                    int idx = 0;
                    while (curr) {
                        Order o = curr->getData();
                        if (o.getArrivalTime() <= current_time) {
                            if (o.getPriority() > best_priority) {
                                best_priority = o.getPriority();
                                best_node_idx = idx;
                                best_node = curr;
                            }
                        }
                        curr = curr->getNext();
                        idx++;
                    }

                    if (best_node) {
                        units[i].working = true;
                        units[i].active_order = new Order(best_node->getData());
                        units[i].time_left = units[i].active_order->getExecutionTime();
                        
                        // Drop it out from list sequence internally freeing memory allocations
                        order_list.remove(best_node_idx);
                    }
                }
            }

            // Snapshot log tracking
            std::vector<std::string> time_step_log;
            for (int i = 0; i < executionUnits; ++i) {
                if (units[i].working && units[i].active_order != nullptr) {
                    time_step_log.push_back(units[i].active_order->getDescription());
                } else {
                    time_step_log.push_back("IDLE");
                }
            }

            result_log.push_back(time_step_log);
            current_time++;
        }

        return result_log;
    }
};

