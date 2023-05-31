#include <iostream>

class DFA {
    int state = 0;
    std::vector<int> finalStates;
    std::vector<char> sigma;
    std::vector<int> states;
    std::vector<std::tuple<int, char, int>> transitions;

public:
    DFA (std::vector<int> finalStates, std::vector<char> sigma, std::vector<int> states,
         std::vector<std::tuple<int, char, int>> transitions) : finalStates(finalStates),
                                                                sigma(sigma), states(states), transitions(transitions) {}

    ~DFA () = default;

    void accepts (std::string input) {
        state = 0;

        for (int i = 0; i < input.length(); i++) {
            int nextState = exists(state, input[i]);
            if (nextState == -1)
                return print(false);
            state = nextState;
        }

        if (std::find(finalStates.begin(), finalStates.end(), state) != finalStates.end())
            return print(true);
        else return print(false);
    }

    void print(bool accepts) {
        if (accepts == true)
            std::cout << "It accepts.\n";
        else std::cout << "It doesn't accept.\n";
    }

    int exists (int state, char sigma) {
        for (auto transition : transitions) {
            if (std::get<0>(transition) == state && std::get<1>(transition) == sigma)
                return std::get<2>(transition);
        }
        return -1;
    }
};

int main() {
    DFA zamfimat({1}, {'a', 'b'}, {0, 1, 2}, {{0, 'a', 1}, {0, 'b', 2}, {1, 'a', 2},
                                              {1, 'b', 1}, {2, 'b', 2}});

    zamfimat.accepts("ab"); // it accepts
    zamfimat.accepts("ba"); // it doesn't accept
    zamfimat.accepts("abbbb"); // it accepts
    return 0;
}