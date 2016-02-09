#include "loopProgram.h"

/*****
  Aim: Draw a plate filled with n of INIT_CREATURES amount of Critters. They are red when born. They look around for other
  members for their species, and try to mate with the most interesting one. They freak() when managing this, which makes them
  blue temporarily. If they can't release themselves after finding a potential partner, they're horny() - turning yellow. for
  a while. MAX_CREATURES filling up will induce this.

  A Critter will inherit their color as a compromise of their parents' colors.
  A Critter has a genetic color, a temporary color (fenotype), and it moves ~randomly. It avoids crossing borders of its world.
  In main() the turn alternates among moving, feeling and mating. '1' ends the simulation.
*****/

int main(int argc, char* argv[]) {
  return loopProgram();
}
