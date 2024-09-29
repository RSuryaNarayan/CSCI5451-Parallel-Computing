#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

/* Gives us high-resolution timers. */
#define _POSIX_C_SOURCE 199309L
#include <time.h>

/* OSX timer includes */
#ifdef __MACH__
  #include <mach/mach.h>
  #include <mach/mach_time.h>
#endif

/**
* @brief Return the number of seconds since an unspecified time (e.g., Unix
*        epoch). This is accomplished with a high-resolution monotonic timer,
*        suitable for performance timing.
*
* @return The number of seconds.
*/
static inline double monotonic_seconds()
{
#ifdef __MACH__
  /* OSX */
  static mach_timebase_info_data_t info;
  static double seconds_per_unit;
  if(seconds_per_unit == 0) {
    mach_timebase_info(&info);
    seconds_per_unit = (info.numer / info.denom) / 1e9;
  }
  return seconds_per_unit * mach_absolute_time();
#else
  /* Linux systems */
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec * 1e-9;
#endif
}

/**
* @brief Output the seconds elapsed while clustering.
*
* @param seconds Seconds spent on k-medoids clustering, excluding IO.
*/
static void print_time(double const seconds)
{
  std::cout << "k-medoids clustering time: " << std::fixed << std::setprecision(4) << seconds << "s" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <filename> <num_clusters> <num_threads>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int N_c = std::stoi(argv[2]);
    std::cout<<"Number of clusters = "<<N_c<<std::endl;
    int num_threads = std::stoi(argv[3]);
    std::cout<<"Number of threads = "<<num_threads<<std::endl;

    // Read data from file
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open " + filename);
    }

    // Read first line to get N and D
    int N, D;
    file >> N >> D;

    // Create and resize the 2D vector
    std::vector<std::vector<double>> data(N, std::vector<double>(D));

    // Read the rest of the file
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < D; ++j) {
            if (!(file >> data[i][j])) {
                throw std::runtime_error("Error reading data from file");
            }
        }
    }

    //test if I am reading the data right
    double start_time = monotonic_seconds();
    for (int i=0; i<N; i++)
    {
      for (int j=0; j<D; j++)
      {
        std::cout<<data[i][j]<<"\t";
      }
      std::cout<<"\n";
    }
    double end_time = monotonic_seconds();

    //print time out
    double elapsed_time = end_time - start_time;
    print_time(elapsed_time);

    //end
    return 0;
}