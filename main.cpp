#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

template <typename K, typename V>
void display_pair(pair<K, V> p){
	cout << p.first << " = $" << p.second << endl;
}

struct PriceUnder{
	double limit;

	PriceUnder(double l){
		limit = l;
	}

	bool operator()(pair<string, double> p) const {
		return p.second < limit;
	}
};

int main() {
	map<string, double> products{
		{"Guitar", 199.99},
		{"Piano", 799.99},
		{"Drums", 249.99},
		{"Violin", 489.99},
		{"Flute", 120.50}
	};

	cout << "Product Inventory\n\n";

	cout << "All Products:\n";
	for_each(products.begin(), products.end(), display_pair<string, double>);
	cout << endl;

	double total_value = accumulate(products.begin(), products.end(), 0.0,
		[](double sum, pair<string, double> p){
			return sum + p.second;
		});

	cout << "Total Inventory Value = $" << total_value << endl;

	double limit = 500.0;
	int under_limit = count_if(products.begin(), products.end(), PriceUnder(limit));
	cout << "Number of products under $" << limit << ": " << under_limit << endl;

	auto iter = find_if(products.begin(), products.end(), PriceUnder(150));
	if (iter != products.end())
		cout << "Found product under $150: " << iter->first << " ($" << iter->second << ")\n";
	else
		cout << "No products found under $150.\n";

	return 0;
}
