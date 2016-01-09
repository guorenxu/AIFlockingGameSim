#ifndef BIGSTATES_H
#define BIGSTATES_H

#include "State.h"
#include "Big.h"
#include "Small.h"
#include "StateCodes.h"

class Big;

class ChaseAll : public State<Big>
{
private:

  ChaseAll(){
	  StateCode = CHASEALL;
	  StealSet = false;
  };

  ChaseAll(const ChaseAll&);
  ChaseAll& operator=(const ChaseAll&);

  bool StealSet;

public:

  static ChaseAll* Instance();//used for singleton design pattern
  
  virtual void Enter(Big* big);

  virtual void Execute(Big* big);

  virtual void Exit(Big* big);
};

class Flee : public State<Big>
{
private:

  Flee(){StateCode = FLEE;};

  Flee(const Flee&);
  Flee& operator=(const Flee&);

public:

  static Flee* Instance();//used for singleton design pattern
  
  virtual void Enter(Big* big);

  virtual void Execute(Big* big);

  virtual void Exit(Big* big);
};

class Steal : public State<Big>
{
private:

  Steal(){StateCode = STEAL;};

  Steal(const Steal&);
  Steal& operator=(const Steal&);

public:

  static Steal* Instance();//used for singleton design pattern
  
  virtual void Enter(Big* big);

  virtual void Execute(Big* big);

  virtual void Exit(Big* big);
};

class AvoidStealer : public State<Big>
{
private:

  AvoidStealer(){StateCode = AVOIDSTEALER;};

  AvoidStealer(const AvoidStealer&);
  AvoidStealer& operator=(const AvoidStealer&);

public:

  static AvoidStealer* Instance();//used for singleton design pattern
  
  virtual void Enter(Big* big);

  virtual void Execute(Big* big);

  virtual void Exit(Big* big);
};

#endif
