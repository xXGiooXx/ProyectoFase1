#include <iostream>
#include<string>
#include<vector>
#include <algorithm> //BIBLIOTECA PARA UTILIZAR LA FUNCION transform()


using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string convert(string& word)
{
	transform(word.begin(), word.end(), word.begin(), ::toupper); // Convertir la entrada taxiCategory en mayúscula
	return word;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string getCategory(int year) 
{
    if (year < 2010) {
        return "Doesnt meet the requirements";
    } else if (year < 2015) {
        return "TRADITIONAL";
    } else {
        return "EXECUTIVE";
    }
}
//////////////////////////////////////////////////////////////Agrupacion de dos valores de retorno/////////////////////////////////////////////////////////////////////////////////////////
struct VerificationData{
	bool exists;
	int position;
};

VerificationData verificationTaxi( vector <string> categories, string taxiCategory) 
{
	VerificationData v;
	v.exists = false;
	for (int i = 0; i < categories.size(); i++) 
	{
		if (categories[i] == taxiCategory) 
		{	// buscar el primer taxi disponible con la categoría correspondiente y retornar un true.       
			v.exists = true;
			v.position = i;	
			break;		
		}
		// si no hay taxis disponibles con la categoría requerida retornar un false.
	}
	return v;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sentTaxi( vector<int>& taxis, vector<int>& nAtaxis, vector<int>& nAyears, vector<int>& nAdriversId, vector<int>& nAphoneNumbers, vector<string>& nAdriversName, 
			 vector<string>& nAdriversLastname, vector<string>& nAinsuranceNumbers, vector<string>& nAplates, vector<string>& nAmodelNames, vector<string>& nAmotorNumbers, vector<string>& nAcategories, 
			 vector<string>& driversName, vector<string>& driversLastname, vector<int>& driversId, vector<string>& insuranceNumbers, vector<int>& phoneNumbers, 
			 vector<string>& modelNames, vector<int>& years, vector<string>& motorNumbers, vector<string>& plates, vector<string>& categories, int position)
{	

	//agregar a la cola de taxis en ruta 
	nAtaxis.push_back(taxis[position]); 
	nAyears.push_back(years[position]);  
	nAdriversId.push_back(driversId[position]);
	nAphoneNumbers.push_back(phoneNumbers[position]);
	nAdriversName.push_back(driversName[position]);
	nAdriversLastname.push_back(driversLastname[position]);
	nAinsuranceNumbers.push_back(insuranceNumbers[position]);
	nAplates.push_back(plates[position]);
	nAmodelNames.push_back(modelNames[position]);
	nAmotorNumbers.push_back(motorNumbers[position]);
	nAcategories.push_back(categories[position]);
	
							
	//quitar el taxi de la cola de taxis disponibles						
	taxis.erase(taxis.begin() + position);
	driversName.erase(driversName.begin() + position);
	driversLastname.erase(driversLastname.begin() + position);
	driversId.erase(driversId.begin() + position);
	insuranceNumbers.erase(insuranceNumbers.begin() + position);
	phoneNumbers.erase(phoneNumbers.begin() + position);
	modelNames.erase(modelNames.begin() + position);
	years.erase(years.begin() + position);
	motorNumbers.erase(motorNumbers.begin() + position);
	plates.erase(plates.begin() + position);
	categories.erase(categories.begin() + position);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void printRouteTaxis(vector<int>& nAtaxis, vector<int>& nAyears, vector<int>& nAdriversId, vector<int>& nAphoneNumbers, vector<string>& nAdriversName, 
					 vector<string>& nAdriversLastname, vector<string>& nAinsuranceNumbers, vector<string>& nAplates, vector<string>& nAmodelNames, 
					 vector<string>& nAmotorNumbers, vector<string>& nAcategories)
{
    TextTable t('-', '|', '+');
    t.add(" Order ");
	t.add(" Taxi ID ");
	t.add(" Driver Name ");
	t.add(" Driver Last Name ");
	t.add(" Driver ID ");
	t.add(" Insurance Number of Driver ");
	t.add(" Phone Number ");
	t.add(" Model Car ");
	t.add(" Year of the Car ");
	t.add(" Motor Number ");
	t.add(" Plate Number "); 
	t.add(" Category ");
    t.endOfRow();
    for (int i = 0; i < nAtaxis.size(); i++)
    {
        t.add(to_string(i));
        t.add(to_string(nAtaxis.at(i)));
        t.add(nAdriversName.at(i));
		t.add(nAdriversLastname.at(i));
		t.add(to_string(nAdriversId.at(i)));
		t.add(nAinsuranceNumbers.at(i));
		t.add(to_string(nAphoneNumbers.at(i)));
		t.add(nAmodelNames.at(i));
		t.add(to_string(nAyears.at(i)));
		t.add(nAmotorNumbers.at(i));
		t.add(nAplates.at(i));
		t.add(nAcategories.at(i));
        t.endOfRow();
    }
    t.setAlignment(2, TextTable::Alignment::LEFT);
    cout << t;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void returnToStandby(vector<int>& taxis, vector<int>& nAtaxis, vector<int>& nAyears, vector<int>& nAdriversId, vector<int>& nAphoneNumbers, vector<string>& nAdriversName, 
					vector<string>& nAdriversLastname, vector<string>& nAinsuranceNumbers, vector<string>& nAplates, vector<string>& nAmodelNames, vector<string>& nAmotorNumbers, vector<string>& nAcategories, 
					vector<string>& driversName, vector<string>& driversLastname, vector<int>& driversId, vector<string>& insuranceNumbers, vector<int>& phoneNumbers, 
					vector<string>& modelNames, vector<int>& years, vector<string>& motorNumbers, vector<string>& plates, vector<string>& categories, int idToReinsert)
{                   
    // Buscar el índice del taxi en ruta según el taxiId
    auto i = find(nAtaxis.begin(), nAtaxis.end(), idToReinsert);
    if (i != nAtaxis.end()) {
        int index = distance(nAtaxis.begin(), i);

        // Agregar el taxi de vuelta a la lista de espera
        taxis.push_back(nAtaxis[index]);
        driversName.push_back(nAdriversName[index]);
        driversLastname.push_back(nAdriversLastname[index]);
        driversId.push_back(nAdriversId[index]);
        insuranceNumbers.push_back(nAinsuranceNumbers[index]);
        phoneNumbers.push_back(nAphoneNumbers[index]);
        modelNames.push_back(nAmodelNames[index]);
        years.push_back(nAyears[index]);
        motorNumbers.push_back(nAmotorNumbers[index]);
        plates.push_back(nAplates[index]);
        categories.push_back(nAcategories[index]);

        // Eliminar el taxi de la lista de taxis en ruta
        nAtaxis.erase(nAtaxis.begin() + index);
        nAdriversName.erase(nAdriversName.begin() + index);
        nAdriversLastname.erase(nAdriversLastname.begin() + index);
        nAdriversId.erase(nAdriversId.begin() + index);
        nAinsuranceNumbers.erase(nAinsuranceNumbers.begin() + index);
        nAphoneNumbers.erase(nAphoneNumbers.begin() + index);
        nAmodelNames.erase(nAmodelNames.begin() + index);
        nAyears.erase(nAyears.begin() + index);
        nAmotorNumbers.erase(nAmotorNumbers.begin() + index);
        nAplates.erase(nAplates.begin() + index);
        nAcategories.erase(nAcategories.begin() + index);
    }
}
