//
//
//  rec02
//
//  Created by Shrey Kharbanda on 2/3/23.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
using namespace std;

struct Molecule{
    vector<string> names;
    int num_carbons;
    int num_hydrogens;
};

void open_file(ifstream& file_name);

void extract_data(vector<Molecule>& molecular_formulas, ifstream& carb_file);

void insert_molecule(const string& molecule_name, Molecule& molecular_formula, vector<Molecule>& molecular_formulas);

size_t find_location(const vector<Molecule>& molecular_formulas, const Molecule& molecular_formula);

void print_formulas(const vector<Molecule>& molecular_formulas);

void print_molecule(const Molecule& molecular_formula);

void sort_formulas(vector<Molecule>& molecular_formulas);

int main() {
    ifstream carb_file;
    open_file(carb_file);
    vector<Molecule> molecular_formulas;
    extract_data(molecular_formulas, carb_file);
    carb_file.close();
    sort_formulas(molecular_formulas);
    print_formulas(molecular_formulas);
}

void open_file(ifstream& file_name){
    do{
        string name;
        cout << "Please enter the file name: ";
        cin >> name;
        file_name.open(name);
    } while (!file_name);
}


void extract_data(vector<Molecule>& molecular_formulas, ifstream& carb_file){
    string molecule_name;
    int num_carbons;
    int num_hydrogens;
    char c;
    //char h;
    while (carb_file >> molecule_name >> c >> num_carbons >> c >> num_hydrogens){
        Molecule molecular_formula;
        molecular_formula.names.push_back(molecule_name);
        molecular_formula.num_carbons = num_carbons;
        molecular_formula.num_hydrogens = num_hydrogens;
        insert_molecule(molecule_name, molecular_formula, molecular_formulas);
    }
}

void insert_molecule(const string& molecule_name, Molecule& molecular_formula, vector<Molecule>& molecular_formulas){
    size_t index;
    index = find_location(molecular_formulas, molecular_formula);
    if (index!= molecular_formulas.size()) {
        molecular_formulas[index].names.push_back(molecule_name);
    } else{
        molecular_formulas.push_back(molecular_formula);
    }
}

size_t find_location(const vector<Molecule>& molecular_formulas, const Molecule& molecular_formula){
    for(size_t index=0; index<molecular_formulas.size(); ++index){
        if (molecular_formulas[index].num_carbons == molecular_formula.num_carbons && molecular_formulas[index].num_hydrogens == molecular_formula.num_hydrogens){
            return (index);
        }
    }
    return (molecular_formulas.size());
}

void print_formulas(const vector<Molecule>& molecular_formulas){
    for (const Molecule& molecular_formula: molecular_formulas){
        print_molecule(molecular_formula);
    }
}

void print_molecule(const Molecule& molecular_formula){
    cout << "C" << molecular_formula.num_carbons << "H" << molecular_formula.num_hydrogens << ' ';
    for (const string& name: molecular_formula.names){
        cout << name << ' ';
    }
    cout << endl;
}

void sort_formulas(vector<Molecule>& molecular_formulas){
    for(size_t cur=1;cur<molecular_formulas.size();++cur){
        for (size_t j=cur; j>=0; --j){
            if (molecular_formulas[j].num_carbons < molecular_formulas[j-1].num_carbons || (molecular_formulas[j].num_carbons == molecular_formulas[j-1].num_carbons && molecular_formulas[j].num_hydrogens < molecular_formulas[j-1].num_hydrogens)){
                swap(molecular_formulas[j], molecular_formulas[j-1]);
            }
            
            else {break;}}
    }
}
