#include <iostream>

#include <vector>
#include <sstream>
#include <ctime>

#include <utility>
#include <tuple>

using namespace std;

struct coordinate
{
    int x, y, z;
    time_t record_time;
    coordinate(int inx, int iny, int inz, time_t t)
    {
        x = inx;
        y = iny;
        z = inz;
        record_time = t;
    }
};

bool str_content_is_int(string s){
    if(s.size() == 0 || s.size() > 11)
        return false;
    if(s[0] == '-'){
        if(s.size() == 1)
            return false;
    }
    else if(s[0] < '0' || s[0] > '9')
        return false;

    for(int i = 1; i < (int)s.size(); ++i)
        if(s[i] < '0' || s[i] > '9')
            return false;

    stringstream ss0;
    ss0.str("");
    long long num;
    ss0 << s;
    ss0 >> num;
    ss0.clear();
    if(num > 2147483647 || num < -2147483648)
        return false;

    return true;
}

int main()
{
    string in_s, in_num;
    int position[3];
    stringstream ss;

    int i;

    vector< pair<string, coordinate> > player_position;
    tuple<int, time_t, time_t, time_t> status;
    get<0>(status) = 0;
    get<1>(status) = clock();

    cout << "Player name(enter \"--\" to stop):" << endl;
    while(cin >> in_s){
        if(in_s == "--")
            break;

        cout << "Coordinate(x, y, z):" << endl;
        for(i = 0; i < 3; ++i){
            cin >> in_num;
            while(!str_content_is_int(in_num)){
                cout << "please enter an integer." << endl;
                cin >> in_num;
            }
            ss.str("");
            ss << in_num;
            ss >> position[i];
            ss.clear();
        }
        player_position.push_back(make_pair(in_s, coordinate(position[0], position[1], position[2], clock())));
        ++get<0>(status);

        cout << "Player name(enter \"--\" to stop):" << endl;
    }
    get<2>(status) = clock();
    get<3>(status) = (get<2>(status) - get<1>(status))/(time_t)get<0>(status);

    cout << "\n";
    for(i = 0; i < (int)player_position.size(); ++i){
        cout << player_position[i].first << " ---- "
            << player_position[i].second.x << ", " << player_position[i].second.y << ", " << player_position[i].second.z << endl;
        cout << "(entered when " << player_position[i].second.record_time/CLOCKS_PER_SEC << " sec(s) passed)" << endl;
    }

    cout << "\n" << "Total: " << get<0>(status) << " record(s)" << endl;
    cout << "Start time: " << get<1>(status)/CLOCKS_PER_SEC << endl;
    cout << "Finish time: " << get<2>(status)/CLOCKS_PER_SEC << endl;
    cout << "Average time spent typing each data: " << get<3>(status)/CLOCKS_PER_SEC << " sec(s)" << endl;

    return 0;
}
