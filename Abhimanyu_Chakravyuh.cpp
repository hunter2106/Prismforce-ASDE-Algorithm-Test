#include <bits/stdc++.h>
using namespace std;

typedef long double ldb;    // shortening the long double to ldb for easier use

const ldb CIRCLE_COUNT = 11;    // number of circles in the Chakravyuh which is 11 (as per the problem statement)

/*
    canCrossChakravyuh function is used to check if Abhimanyu can cross the Chakravyuh
    k is the vector for each enemy circle power in the Chakravyuh
    p_cur is the current power of Abhimanyu
    p_original is the original power of Abhimanyu
    a is the boon to skip fighting enemies (number of times he can skip over an enemy)
    b is the number of times Abhimanyu can recharge his power
    i is the index of the current circle
    is_possible is a boolean variable to check if Abhimanyu can cross the Chakravyuh
*/
void canCrossChakravyuh(vector<ldb> &k, ldb p_cur, ldb &p_original, ldb a, ldb b, ldb i, bool &is_possible)
{
    // if all the circles are crossed then set is_possible to true (meaning Abhimanyu can cross the Chakravyuh)
    if (i == CIRCLE_COUNT)
    {
        is_possible = true;
        return;
    }

    /*
    Intial recursion call to check
    if Abhimanyu has boon to skip fighting enemies then skip the current circle and move to the next circle
    */
    if (a)
    {
        canCrossChakravyuh(k, p_cur, p_original, a - 1, b, i + 1, is_possible);
    }
    // if the skip is not available or returning after skipping the circle then check if Abhimanyu can fight the current circle


    if (i == 2 || i == 6)    // if the current circle is 3rd (i == 2) or 7th (i == 6) circle then Abhimanyu can divide the power of the circle by 2
    {
        ldb b_tmp = b;    // store the value of b in b_tmp for backtracking

        if (p_cur < k[i])    // if the current power of Abhimanyu is less than the power of the current circle then check if he can recharge his power
        {
            if (p_original < k[i] || !b)    // if the original power of Abhimanyu is less than the power of the current circle or he cannot recharge his power then return
            {
                return;
            }

            b--;
            p_cur = p_original;
        }

        ldb k_tmp = k[i];    // store the value of k[i] in k_tmp for backtracking
        k[i] /= (ldb)2;

        canCrossChakravyuh(k, p_cur - k_tmp, p_original, a, b, i + 1, is_possible);

        k[i] = k_tmp;
        b = b_tmp;
    }
    else if (i == 3 || i == 7)  // if the current circle is 4th (i == 3) or 8th (i == 7) circle then Abhimanyu will have to fight both previous and current circle
    {
        // these variables has the same purpose as above
        ldb b_tmp = b;

        if (p_cur < k[i] + k[i - 1])
        {
            if (p_original < k[i] + k[i - 1] || !b)
            {
                return;
            }

            b--;
            p_cur = p_original;
        }

        canCrossChakravyuh(k, p_cur - k[i] - k[i - 1], p_original, a, b, i + 1, is_possible);

        b = b_tmp;
    }
    else    // rest of the circles that Abhimanyu has to fight
    {
        // these variables has the same purpose as above
        ldb b_tmp = b;

        if (p_cur < k[i])
        {
            if (p_original < k[i] || !b)
            {
                return;
            }

            b--;
            p_cur = p_original;
        }

        canCrossChakravyuh(k, p_cur - k[i], p_original, a, b, i + 1, is_possible);

        b = b_tmp;
    }
}

int main()
{
    // testset file names and output file names
    vector<string> testset = {"testset_1.txt", "testset_2.txt"};
    vector<string> output = {"output_1.txt", "output_2.txt"};

    for (int test_index = 0; test_index < 2; test_index++)
    {
        // freopen is used to read input from a file and write output to a file
        freopen(testset[test_index].c_str(), "r", stdin);
        freopen(output[test_index].c_str(), "w", stdout);

        // number of testcases
        int testcases;
        cin >> testcases;

        while (testcases--)
        {
            // k is the vector for each enemy circle power in the Chakravyuh
            vector<ldb> k(CIRCLE_COUNT);
            for (ldb i = 0; i < CIRCLE_COUNT; i++)
            {
                cin >> k[i];
            }

            /*
                p is the power of Abhimanyu
                a is the boon to skip fighting enemies (number of times he can skip over an enemy)
                b is the number of times Abhimanyu can recharge his power
            */
            ldb p, a, b;
            cin >> p >> a >> b;

            // is_possible is a boolean variable to check if Abhimanyu can cross the Chakravyuh
            bool is_possible = false;

            canCrossChakravyuh(k, p, p, a, b, 0, is_possible);

            if (is_possible)
            {
                cout << "YES, Abhimanyu can cross the Chakravyuh to reach Pandavas" << "\n";
            }
            else
            {
                cout << "NO, Abhimanyu cannot cross the Chakravyuh" << "\n";
            }
        }
    }

    return 0;
}