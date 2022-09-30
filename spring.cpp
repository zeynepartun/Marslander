#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace std::chrono;


void euler_calc(double m, double k, double x, double v, double t_max, double dt){
  double t, a;
  vector<double> t_list, x_list, v_list;

  // mass, spring constant, initial position and velocity
  // m = 1;
  // k = 1;
  // x = 0;
  // v = 1;

  // simulation time and timestep
  // t_max = 100;
  // dt = 0.001;

  // Euler integration
  for (t = 0; t <= t_max; t = t + dt) {

    // append current state to trajectories
    t_list.push_back(t);
    x_list.push_back(x);
    v_list.push_back(v);

    // calculate new position and velocity
    a = -k * x / m;
    x = x + dt * v;
    v = v + dt * a;

  }
  // Write the trajectories to file
  ofstream fout;
  fout.open("euler_trajectories.txt");
  if (fout) { // file opened successfully
    for (int i = 0; i < t_list.size(); i = i + 1) {
      fout << t_list[i] << ' ' << x_list[i] << ' ' << v_list[i] << endl;
    }
  } else { // file did not open successfully
    cout << "Could not open trajectory file for writing" << endl;
  }
}

  //Verlet integration
void verlet_calc(double m, double k, double x, double v, double t_max, double dt){
  double t, a, xmin1, xold;
  vector<double> t_list, x_list, v_list ;
  xmin1 = -v*dt + x;
  

  for (t = 0; t <= t_max; t = t + dt) {
    xold = x;
    // append current state to trajectories
    t_list.push_back(t);
    x_list.push_back(x);
    v_list.push_back(v);

    // calculate new position and velocity
    
    a = -k * x / m;
    x = 2*(x) - xmin1 + (dt*dt)* a;
    xmin1 = xold;
  }




  // Write the trajectories to file
  ofstream fout;
  fout.open("verlet_trajectories.txt");
  if (fout) { // file opened successfully
    for (int i = 0; i < t_list.size(); i = i + 1) {
      fout << t_list[i] << ' ' << x_list[i] << ' ' << v_list[i] << endl;
    }
  } else { // file did not open successfully
    cout << "Could not open trajectory file for writing" << endl;
  }
}

int main() {

  // declare variables
  high_resolution_clock::time_point endtime, starttime = high_resolution_clock::now();
  microseconds duration;
  

  euler_calc(1, 1, 0, 1, 100, 0.001);
  verlet_calc(1, 1, 0, 1, 100, 0.001);
  
  // double m, k, x, v, t_max, dt, t, a;
  // vector<double> t_list, x_list, v_list;

  // // mass, spring constant, initial position and velocity
  // m = 1;
  // k = 1;
  // x = 0;
  // v = 1;

  // // simulation time and timestep
  // t_max = 100;
  // dt = 0.001;

  // // Euler integration
  // for (t = 0; t <= t_max; t = t + dt) {

  //   // append current state to trajectories
  //   t_list.push_back(t);
  //   x_list.push_back(x);
  //   v_list.push_back(v);

  //   // calculate new position and velocity
  //   a = -k * x / m;
  //   x = x + dt * v;
  //   v = v + dt * a;

  // }

  // //Verlet integration


  // // Write the trajectories to file
  // ofstream fout;
  // fout.open("trajectories.txt");
  // if (fout) { // file opened successfully
  //   for (int i = 0; i < t_list.size(); i = i + 1) {
  //     fout << t_list[i] << ' ' << x_list[i] << ' ' << v_list[i] << endl;
  //   }
  // } else { // file did not open successfully
  //   cout << "Could not open trajectory file for writing" << endl;
  // }

  endtime = high_resolution_clock::now();
  duration = duration_cast<microseconds>(endtime - starttime);

  cout << "Time taken by function: "
    << duration.count() << " microseconds" << endl;


  return 0;
  
  /* The file can be loaded and visualised in Python as follows:

  import numpy as np
  import matplotlib.pyplot as plt
  results = np.loadtxt('trajectories.txt')
  plt.figure(1)
  plt.clf()
  plt.xlabel('time (s)')
  plt.grid()
  plt.plot(results[:, 0], results[:, 1], label='x (m)')
  plt.plot(results[:, 0], results[:, 2], label='v (m/s)')
  plt.legend()
  plt.show()

  */
}
