#ifndef TEAMSTATES_H
#define TEAMSTATES_H

#include "State.h"
#include "Big.h"
#include "Small.h"
#include "Team.h"
#include "StateCodes.h"

class Team;

class Offensive : public State<Team>
{
private:

  Offensive(){
	  StateCode = OFFENSIVE;
  };

  Offensive(const Offensive&);
  Offensive& operator=(const Offensive&);

public:

  static Offensive* Instance();//used for singleton design pattern
  
  virtual void Enter(Team* team);

  virtual void Execute(Team* team);

  virtual void Exit(Team* team);
};

class Defensive : public State<Team>
{
private:

  Defensive(){
	  StateCode = DEFENSIVE;
  };

  Defensive(const Offensive&);
  Defensive& operator=(const Defensive&);

public:

  static Defensive* Instance();//used for singleton design pattern
  
  virtual void Enter(Team* team);

  virtual void Execute(Team* team);

  virtual void Exit(Team* team);
};


#endif