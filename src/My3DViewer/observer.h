#ifndef OBSERVER_H
#define OBSERVER_H

#include <QPushButton>
#include <QWidget>

namespace s21 {

class IObserver {
 public:
  virtual void updates() = 0;
};

class ISubject {
 public:
  virtual void attach(IObserver* observer) = 0;
  virtual void detach(IObserver* observer) = 0;
  virtual void notify() = 0;
};

class QCustomPushButton : public ISubject, public QPushButton {
 public:
  QCustomPushButton(const QString& text, QWidget* parent = nullptr)
      : QPushButton(text, parent) {}
  void attach(IObserver* observer) override;
  void detach(IObserver* observer) override;
  void notify() override;

 private:
  std::vector<IObserver*> observers;
};

}  // namespace s21

#endif  // OBSERVER_H
