#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <unordered_map>

using namespace std;

// Funcion para convertir binario a hexadecimal
string binaryToHex(string binary) {
    int pointPos = binary.find('.');

    string intPart = binary.substr(0, pointPos);
    string fracPart = pointPos != string::npos ? binary.substr(pointPos + 1) : "";

    // Conversion de la parte entera
    unsigned long long int intDecimal = stoull(intPart, nullptr, 2);
    stringstream hexStream;
    hexStream << hex << intDecimal;
    string hexInteger = hexStream.str();

    // Conversion de la parte fraccionaria
    double fracDecimal = 0.0;
    if (!fracPart.empty()) {
        for (size_t i = 0; i < fracPart.size(); ++i) {
            if (fracPart[i] == '1') {
                fracDecimal += 1.0 / (1 << (i + 1));
            }
        }
    }

    string hexFractional = "";
    while (fracDecimal != 0.0) {
        fracDecimal *= 16;
        int fracInt = static_cast<int>(fracDecimal);
        hexFractional += (fracInt < 10) ? to_string(fracInt) : string(1, 'A' + fracInt - 10);
        fracDecimal -= fracInt;

        if (hexFractional.size() > 10) {  // Limitar a 10 
            break;
        }
    }

    return fracPart.empty() ? hexInteger : hexInteger + "." + hexFractional;
}

// Funcion para calcular el complemento restringido de un num bin
string restrictedComplement(string binary) {
    if (binary.empty()) return "Error: Cadena vacía";

    // El primer bit (bit de signo) se mantiene, los demás se invierten
    string complement = binary[0] == '0' ? "0" : "1";  // Mantiene el primer bit
    for (size_t i = 1; i < binary.size(); ++i) {
        complement += (binary[i] == '0') ? '1' : '0';  // Invertir bits
    }
    return complement;
}

// Función para convertir decimal a hexadecimal (con manejo de periodicidad)
string decimalToHex(string decimal) {
    int pointPos = decimal.find('.');

    string intPart = decimal.substr(0, pointPos);
    string fracPart = pointPos != string::npos ? decimal.substr(pointPos + 1) : "";

    // Convertir la parte entera a hexadecimal
    unsigned long long int intDecimal = stoull(intPart);
    stringstream hexStream;
    hexStream << hex << intDecimal;
    string hexInteger = hexStream.str();

    // Conversion de la parte fraccionaria
    double fracDecimal = fracPart.empty() ? 0.0 : stod("0." + fracPart);
    unordered_map<double, int> seen;
    string hexFractional = "";
    int repeatStart = -1;

    for (int i = 0; fracDecimal != 0.0 && i < 20; ++i) {  // Limitar a 20 digitos
        if (seen.find(fracDecimal) != seen.end()) {
            repeatStart = seen[fracDecimal];
            break;
        }

        seen[fracDecimal] = i;
        fracDecimal *= 16;
        int fracInt = static_cast<int>(fracDecimal);
        hexFractional += (fracInt < 10) ? to_string(fracInt) : string(1, 'A' + fracInt - 10);
        fracDecimal -= fracInt;
    }

    if (repeatStart != -1) {
        hexFractional = hexFractional.substr(0, repeatStart) + "(" + hexFractional.substr(repeatStart) + ")";
    }

    return fracPart.empty() ? hexInteger : hexInteger + "." + hexFractional;
}

// Funcion menu
void displayMenu() {
    cout << "\n===== Menu de Operaciones =====" << endl;
    cout << "1. Conversion de Binario a Hexadecimal" << endl;
    cout << "2. Obtener el Complemento Restringido de un Numero Binario" << endl;
    cout << "3. Conversion de Decimal a Hexadecimal" << endl;
    cout << "4. Salir" << endl;
    cout << "================================" << endl;
}

int main() {
    while (true) {
        displayMenu();
        int choice;
        cout << "Selecciona una opcion (1-4): ";
        cin >> choice;

        if (choice == 1) {
            string binary;
            cout << "Introduce el numero binario (ejemplo: 1010.101): ";
            cin >> binary;
            cout << "Hexadecimal: " << binaryToHex(binary) << endl;
        }
        else if (choice == 2) {
            string binary;
            cout << "Introduce el numero binario: ";
            cin >> binary;
            cout << "Complemento Restringido: " << restrictedComplement(binary) << endl;
        }
        else if (choice == 3) {
            string decimal;
            cout << "Introduce el numero decimal (ejemplo: 10.625): ";
            cin >> decimal;
            cout << "Hexadecimal: " << decimalToHex(decimal) << endl;
        }
        else if (choice == 4) {
            cout << "Gracias! Hasta luego" << endl;
            break;
        }
        else {
            cout << "Opcion invalida. Elige una opcion entre 1 y 4" << endl;
        }

        // Preguntar si el usuario desea realizar otra operación
        char again;
        cout << "Deseas realizar otra operacion? (s/n): ";
        cin >> again;
        if (again == 'n' || again == 'N') {
            cout << "Gracias! Hasta luego" << endl;
            break;
        }
    }

    return 0;
}
