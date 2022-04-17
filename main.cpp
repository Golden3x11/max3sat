#include "Problem.h"
#include "Optimizer.h"
#include "Timer.h"

#include <exception>
#include <iostream>

using namespace std;
using namespace TimeCounters;

#define dMAX_TIME 1  * 60


void vRunExperiment(CProblem *pcProblem)
{
    for(int i=0;i<1;i++) {
        try {
            CTimeCounter c_time_counter;

            double d_time_passed;

            COptimizer c_optimizer(pcProblem);

            c_time_counter.vSetStartNow();


            c_optimizer.vInitialize();

            cout << c_optimizer.pcGetBestFound()->fitness(pcProblem->iGetNumberClauses()) << endl;

            c_time_counter.bGetTimePassed(&d_time_passed);
            int time10s = 10, x = 0;
            while (d_time_passed <= dMAX_TIME) {
                c_optimizer.vRunIteration();
                c_optimizer.pcGetBestFound();
                x++;
                if (d_time_passed > time10s) {
                    cout.width(4);
                    cout << time10s << "s,";
                    if (time10s % 60 == 0) {
                        cout << "-> " << c_optimizer.pcGetBestFound()->fitness(pcProblem->iGetNumberClauses()) << "\t"
                             << x << endl;
                        x = 0;
                    }
                    time10s += 10;
                }

                c_time_counter.bGetTimePassed(&d_time_passed);
            }//while (d_time_passed <= MAX_TIME)
            cout.width(4);
            cout << time10s << "s," << "-> " << c_optimizer.pcGetBestFound()->fitness(pcProblem->iGetNumberClauses())
                 << "\t" << x << endl;
            cout << c_optimizer.pcGetBestFound()->getCompletedClauses() << '/' << pcProblem->iGetNumberClauses()
                 << endl;
            //c_optimizer.pcGetBestFound()->piGetResultAsTable();
        }//try
        catch (exception &c_exception) {
            cout << c_exception.what() << endl;
        }//catch (exception &c_exception)
    }
}//void vRunExperiment(const CEvaluator &cConfiguredEvaluator)


int main(int iArgCount, char **ppcArgValues)
{

    CProblem  c_problem;

    if (c_problem.bLoad(R"(C:\Users\Konrad\Downloads\max3sat\max3sat\350\m3s_350_0.txt)"))
    {
        vRunExperiment(&c_problem);
    }//if (c_problem.bLoad("m3s_100_2") == true)

}//void main(int iArgCount, char **ppcArgValues)
