#include "observer.h"
using namespace s21;

void QCustomPushButton::attach(IObserver *observer) {
  observers.push_back(observer);
}

void QCustomPushButton::detach(IObserver *observer) {
  observers.erase(std::remove(observers.begin(), observers.end(), observer),
                  observers.end());
}

void QCustomPushButton::notify() {
  for (auto observer : observers) {
    observer->updates();
  }
}
