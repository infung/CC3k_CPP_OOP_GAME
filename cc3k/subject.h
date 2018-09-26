#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "subscriptiontype.h"
#include <memory>

class Info;
class Observer;

class Subject {
  std::vector<std::shared_ptr<Observer>> observers;
  int x;
  int y;
  char display; 
 protected:
  int getX() const;
  int getY() const;
 public:
  void reset();
  void setX(int X);
  void setY(int Y);
  Subject(char c);
  char getDisplay() const;
  void setDisplay(char c);
  void attach(std::shared_ptr<Observer> o);  
  void detach(std::shared_ptr<Observer> o);
  void notifyObservers(SubscriptionType t);
  virtual Info getInfo() const = 0;
  virtual ~Subject() = 0;
};

#endif


