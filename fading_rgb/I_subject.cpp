#include "I_subject.h"

I_subject::I_subject(const int& signal) : signal(signal) {
    receiver_ptr = nullptr;
    receiver_count = 0;
};

I_subject::~I_subject() {
    if (receiver_ptr){
        delete[] receiver_ptr;
    }

};


void I_subject::add_observer(I_observer *receiver) {
    ++receiver_count;
    I_observer **old = receiver_ptr;
    receiver_ptr = new I_observer*[receiver_count];
    for (int i = 0; i != receiver_count - 1; ++i){
        receiver_ptr[i] = old[i];
    }
    receiver_ptr[receiver_count - 1] = receiver;
    delete[] old;
};


void I_subject::send_interaction() {
        
        for (int i = 0; i != receiver_count; ++i) {
            receiver_ptr[i]->interact(signal);};
        }
