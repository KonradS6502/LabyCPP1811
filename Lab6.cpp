#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <memory>

class IGate {
public:
	virtual int evaluate() = 0;
	virtual void print() const = 0;
	virtual ~IGate() = default;
};

class Gate : public IGate {
public:
	Gate(std::map<int, int>& nodes) : node(nodes){};
	virtual ~Gate() = default;
	std::map<int, int> Get_map(void) {
		return node;
	}
private:
	std::map<int, int> node;
};

class AndGate : public Gate {
public:
	int index_input1;
	int index_input2;
	int index_output;
	int evaluate() override {
		if (Get_map()[index_input1] == -1 || Get_map()[index_input2] == -1) {
			return -1;
		}

		else {
			return(Get_map()[index_input1] & Get_map()[index_input2]);
		}

	};


	void print() const override {
		std::cout << index_input1 <<"_" << index_input2 << "_" << index_output << "\n";
	}
	AndGate(int ii1, int ii2, int io, std::map<int, int>& nodes) : index_input1(ii1), index_input2(ii2), index_output(io), Gate(nodes) {};
	virtual ~AndGate() = default;
private:
};


class OrGate : public Gate {
public:
	int index_input1;
	int index_input2;
	int index_output;
	int evaluate() override {
		if (Get_map()[index_input1] == -1 || Get_map()[index_input2] == -1) {
			return -1;
		}

		else {
			return(Get_map()[index_input1] | Get_map()[index_input2]);
		}

	};


	void print() const override {
		std::cout << index_input1 << "_" << index_input2 << "_" << index_output << "\n";
	}
	OrGate(int ii1, int ii2, int io, std::map<int, int>& nodes) : index_input1(ii1), index_input2(ii2), index_output(io), Gate(nodes) {};
	virtual ~OrGate() = default;
private:
};


class XorGate : public Gate {
public:
	int index_input1;
	int index_input2;
	int index_output;
	int evaluate() override {
		if (Get_map()[index_input1] == -1 || Get_map()[index_input2] == -1) {
			return -1;
		}

		else {
			return(Get_map()[index_input1] ^ Get_map()[index_input2]);
		}

	};


	void print() const override {
		std::cout << index_input1 << "_" << index_input2 << "_" << index_output << "\n";
	}
	XorGate(int ii1, int ii2, int io, std::map<int, int>& nodes) : index_input1(ii1), index_input2(ii2), index_output(io), Gate(nodes) {};
	virtual ~XorGate() = default;
private:
};


class NotGate : public Gate {
public:
	int index_input1;
	int index_output;
	int evaluate() override {
		if (Get_map()[index_input1] == -1) {
			return -1;
		}

		else {
			return(~Get_map()[index_input1]);
		}

	};


	void print() const override {
		std::cout << index_input1 << "_" << index_output << "\n";
	}
	NotGate(int ii1, int io, std::map<int, int>& nodes) : index_input1(ii1), index_output(io), Gate(nodes) {};
	virtual ~NotGate() = default;
private:
};

void print_nodes(const std::map<int, int>& nodes) {
	for (auto i = nodes.cbegin(); i != nodes.cend(); i++) {
		std::cout << i->first << " : " << i->second << "\n";
	}
}
int main()
{
	std::vector<std::shared_ptr<Gate>> gates;
	std::map<int, int> nodes;
	std::string temp_str;
	std::string gate_name_str;

	while (1) {
		std::cin >> temp_str;
		if (temp_str == "end") {
			break;
		}

		if (temp_str == "and" || temp_str == "xor" || temp_str == "or") {
			gate_name_str = temp_str;
			std::cin >> temp_str;
			int index_input1 = std::stoi(temp_str);
			std::cin >> temp_str;
			int index_input2 = std::stoi(temp_str);
			std::cin >> temp_str;
			int index_output = std::stoi(temp_str);
			if (gate_name_str == "and") {
				gates.emplace_back(std::make_shared<AndGate>(index_input1, index_input2, index_output, nodes));
			}
			else if (gate_name_str == "or") {
				gates.emplace_back(std::make_shared<OrGate>(index_input1, index_input2, index_output, nodes));
			}
			else if (gate_name_str == "xor") {
				gates.emplace_back(std::make_shared<XorGate>(index_input1, index_input2, index_output, nodes));
			}
			}

		if (temp_str == "not") {
			std::cin >> temp_str;
			int index_input = std::stoi(temp_str);
			std::cin >> temp_str;
			int index_output = std::stoi(temp_str);
			gates.emplace_back(std::make_unique<NotGate>(index_input, index_output, nodes));
		}

	}
	

	while (1) {
		std::cin >> temp_str;
		int node_index = std::stoi(temp_str);
		if (node_index == -1) {
			break;
		}
		else {
			std::cin >> temp_str;
			int node_state = std::stoi(temp_str);
			nodes[node_index] = node_state;
		}
	}
	for (auto i = 0; i < gates.size(); i++) {
		int evaluation_state = gates[i]->evaluate();
		std::cout << "Stan:"<< evaluation_state << "\n";
		if (evaluation_state == -1) {
			i = 0;
		}
	}
	print_nodes(nodes);
	
}

