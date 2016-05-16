#include "connector/include/mysql_connection.h"
#include "connector/include/cppconn/driver.h"
#include "connector/include/cppconn/exception.h"
#include "connector/include/cppconn/resultset.h"
#include "connector/include/cppconn/statement.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;
string help = "+-----------------------------+------+\n| name                        | id   |\n+-----------------------------+------+\n| Abrantes                    | 1102 |\n| Acacias                     | 519  |\n| Aeropuerto T1 T2 T3         | 806  |\n| Aeropuerto T4               | 808  |\n| Alameda de Osuna            | 552  |\n| Alcorcón Central            | 1203 |\n| Alfonso XIII                | 413  |\n| Almendrales                 | 3124 |\n| Alonso Cano                 | 712  |\n| Alonso de Mendoza           | 1219 |\n| Alonso Martínez             | 404  |\n| Alsacia                     | 253  |\n| Alto de Extremadura         | 627  |\n| Alto del Arenal             | 24   |\n| Aluche                      | 527  |\n| Alvarado                    | 6    |\n| Álvarez de Villaamil        | 5115 |\n| Antón Martín                | 15   |\n| Antonio Machado             | 718  |\n| Antonio Saura               | 5114 |\n| Arganda del Rey             | 928  |\n| Arganzuela - Planetario     | 608  |\n| Argüelles                   | 310  |\n| Arroyo Culebro              | 1217 |\n| Artilleros                  | 917  |\n| Arturo Soria                | 415  |\n| Ascao                       | 705  |\n| Atocha                      | 16   |\n| Atocha Renfe                | 17   |\n| Avenida de América          | 411  |\n| Avenida de Europa           | 5222 |\n| Avenida de Guadalajara      | 254  |\n| Avenida de la Ilustración   | 720  |\n| Avenida de la Paz           | 414  |\n| Aviación Española           | 1018 |\n| Bambú                       | 152  |\n| Banco de España             | 35   |\n| Barajas                     | 807  |\n| Barrio de la Concepción     | 707  |\n| Barrio del Pilar            | 902  |\n| Barrio del Puerto           | 754  |\n| Batán                       | 1014 |\n| Baunatal                    | 1059 |\n| Begoña                      | 1002 |\n| Bélgica                     | 5219 |\n| Berna                       | 5223 |\n| Bilbao                      | 10   |\n| Blasco Ibáñez               | 5116 |\n| Boadilla Centro             | 5325 |\n| Buenos Aires                | 23   |\n| Callao                      | 307  |\n| Campamento                  | 529  |\n| Campo de las Naciones       | 805  |\n| Campus de Somosaguas        | 5221 |\n| Canal                       | 42   |\n| Canillas                    | 417  |\n| Canillejas                  | 501  |\n| Cantabria                   | 5322 |\n| Carabanchel                 | 525  |\n| Carabanchel Alto            | 1105 |\n| Carpetana                   | 602  |\n| Cartagena                   | 709  |\n| Casa de Campo               | 530  |\n| Casa del Reloj              | 1227 |\n| Chamartín                   | 1    |\n| Chueca                      | 513  |\n| Ciudad de la Imagen         | 5312 |\n| Ciudad de los Ángeles       | 354  |\n| Ciudad del Cine             | 5314 |\n| Ciudad Lineal               | 504  |\n| Ciudad Universitaria        | 622  |\n| Cocheras                    | 5315 |\n| Colombia                    | 802  |\n| Colón                       | 405  |\n| Colonia de los Ángeles      | 5213 |\n| Colonia Jardín              | 1016 |\n| Concha Espina               | 908  |\n| Conde de Casal              | 611  |\n| Congosto                    | 28   |\n| Conservatorio               | 1218 |\n| Coslada Central             | 755  |\n| Cruz del Rayo               | 909  |\n| Cuatro Caminos              | 7    |\n| Cuatro Vientos              | 1019 |\n| Cuzco                       | 1005 |\n| Delicias                    | 302  |\n| Diego de León               | 410  |\n| Dos Castillas               | 5220 |\n| Duque de Pastrana           | 905  |\n| El Bercial                  | 1224 |\n| El Capricho                 | 551  |\n| El Carmen                   | 507  |\n| El Carrascal                | 1225 |\n| El Casar                    | 1222 |\n| Embajadores                 | 304  |\n| Empalme                     | 528  |\n| Esperanza                   | 416  |\n| Estación de Aravaca         | 5224 |\n| Estadio Olímpico            | 751  |\n| Estrecho                    | 5    |\n| Estrella                    | 915  |\n| Eugenia de Montijo          | 526  |\n| Ferial de Boadilla          | 5324 |\n| Francos Rodríguez           | 716  |\n| Fuencarral                  | 1001 |\n| Fuenlabrada Central         | 1214 |\n| Fuente de la Mora           | 5112 |\n| García Noblejas             | 704  |\n| Getafe Central              | 1220 |\n| Goya                        | 32   |\n| Gran Vía                    | 12   |\n| Gregorio Marañón            | 711  |\n| Guzmán el Bueno             | 620  |\n| Henares                     | 759  |\n| Herrera Oria                | 901  |\n| Hortaleza                   | 421  |\n| Hospital 12 de Octubre      | 352  |\n| Hospital de Fuenlabrada     | 1212 |\n| Hospital de Móstoles        | 1208 |\n| Hospital del Henares        | 760  |\n| Hospital Infanta Sofía      | 1061 |\n| Hospital Severo Ochoa       | 1228 |\n| Ibiza                       | 913  |\n| Iglesia                     | 9    |\n| Infante Don Luís            | 5328 |\n| Islas Filipinas             | 714  |\n| Jarama                      | 758  |\n| Joaquín Vilumbrales         | 1020 |\n| José Isbert                 | 5313 |\n| Juan de la Cierva           | 1221 |\n| Julián Besteiro             | 1226 |\n| La Almudena                 | 252  |\n| La Elipa                    | 29   |\n| La Fortuna                  | 1107 |\n| La Gavia                    | 128  |\n| La Granja                   | 1055 |\n| La Latina                   | 517  |\n| La Moraleja                 | 1056 |\n| La Peseta                   | 1106 |\n| La Poveda                   | 927  |\n| La Rambla                   | 756  |\n| Lacoma                      | 721  |\n| Lago                        | 1013 |\n| Laguna                      | 601  |\n| Las Musas                   | 701  |\n| Las Rosas                   | 255  |\n| Las Suertes                 | 129  |\n| Las Tablas                  | 1053 |\n| Lavapiés                    | 305  |\n| Leganés Central             | 1229 |\n| Legazpi                     | 301  |\n| Lista                       | 409  |\n| Loranca                     | 1210 |\n| Los Espartales              | 1223 |\n| Lucero                      | 628  |\n| Manoteras                   | 422  |\n| Manuel Becerra              | 31   |\n| Manuel de Falla             | 1058 |\n| Manuela Malasaña            | 1209 |\n| Mar de Cristal              | 418  |\n| María Tudor                 | 5117 |\n| Marqués de la Valdavia      | 1057 |\n| Marqués de Vadillo          | 521  |\n| Méndez Álvaro               | 609  |\n| Menéndez Pelayo             | 18   |\n| Metropolitano               | 621  |\n| Miguel Hernández            | 25   |\n| Mirasierra                  | 951  |\n| Moncloa                     | 311  |\n| Montecarmelo                | 1052 |\n| Montepríncipe               | 5318 |\n| Móstoles Central            | 1206 |\n| Noviciado                   | 39   |\n| Nueva Numancia              | 21   |\n| Nuevo Mundo                 | 5326 |\n| Nuevos Ministerios          | 618  |\n| Núñez de Balboa             | 510  |\n| O'Donnell                   | 613  |\n| Opañel                      | 604  |\n| Ópera                       | 37   |\n| Oporto                      | 523  |\n| Pacífico                    | 19   |\n| Paco de Lucía               | 952  |\n| Palas de Rey                | 5118 |\n| Palos de la Frontera        | 303  |\n| Pan Bendito                 | 1103 |\n| Parque de las Avenidas      | 708  |\n| Parque de los Estados       | 1215 |\n| Parque de Santa María       | 420  |\n| Parque Europa               | 1213 |\n| Parque Lisboa               | 1202 |\n| Parque Oeste                | 1204 |\n| Pavones                     | 918  |\n| Peñagrande                  | 719  |\n| Pinar de Chamartín          | 153  |\n| Pinar del Rey               | 803  |\n| Pío XII                     | 906  |\n| Pirámides                   | 520  |\n| Pitis                       | 723  |\n| Plaza de Castilla           | 2    |\n| Plaza de España             | 308  |\n| Plaza Elíptica              | 605  |\n| Portazgo                    | 22   |\n| Pozuelo Oeste               | 5217 |\n| Pradillo                    | 1207 |\n| Prado de la Vega            | 5212 |\n| Prado del Espino            | 5320 |\n| Prado del Rey               | 5214 |\n| Príncipe de Vergara         | 33   |\n| Principe Pío                | 625  |\n| Prosperidad                 | 412  |\n| Pueblo Nuevo                | 505  |\n| Puente de Vallecas          | 20   |\n| Puerta de Arganda           | 922  |\n| Puerta de Boadilla          | 5329 |\n| Puerta de Toledo            | 518  |\n| Puerta del Ángel            | 626  |\n| Puerta del Sur              | 1021 |\n| Quevedo                     | 41   |\n| Quintana                    | 506  |\n| República Argentina         | 617  |\n| Retamares                   | 5316 |\n| Retiro                      | 34   |\n| Reyes Católicos             | 1060 |\n| Ríos Rosas                  | 8    |\n| Rivas Futura                | 925  |\n| Rivas Urbanizaciones        | 924  |\n| Rivas Vaciamadrid           | 926  |\n| Ronda de la Comunicación    | 1054 |\n| Rubén Darío                 | 511  |\n| Sainz de Baranda            | 612  |\n| San Bernardo                | 40   |\n| San Blas                    | 702  |\n| San Cipriano                | 921  |\n| San Cristóbal               | 356  |\n| San Fermín - Orcasur        | 353  |\n| San Fernando                | 757  |\n| San Francisco               | 1104 |\n| San Lorenzo                 | 419  |\n| San Nicasio                 | 1230 |\n| Santiago Bernabéu           | 1006 |\n| Santo Domingo               | 38   |\n| Serrano                     | 406  |\n| Sevilla                     | 36   |\n| Sierra de Guadalupe         | 26   |\n| Siglo XXI                   | 5327 |\n| Simancas                    | 703  |\n| Somosaguas Centro           | 5216 |\n| Somosaguas Sur              | 5215 |\n| Suanzes                     | 503  |\n| Tetuán                      | 4    |\n| Tirso de Molina             | 14   |\n| Torre Arias                 | 502  |\n| Tres Olivos                 | 1051 |\n| Tribunal                    | 11   |\n| Universidad Rey Juan Carlos | 1205 |\n| Urgel                       | 522  |\n| Usera                       | 606  |\n| Valdeacederas               | 3    |\n| Valdebernardo               | 919  |\n| Valdecarros                 | 130  |\n| Valdezarza                  | 717  |\n| Velázquez                   | 407  |\n| Ventas                      | 30   |\n| Ventilla                    | 903  |\n| Ventorro del Cano           | 5319 |\n| Ventura Rodríguez           | 309  |\n| Vicálvaro                   | 920  |\n| Villa de Vallecas           | 27   |\n| Villaverde Alto             | 357  |\n| Villaverde Bajo Cruce       | 355  |\n| Vinateros                   | 916  |\n| Virgen del Cortijo          | 5113 |\n| Vista Alegre                | 524  |\n| Vodafone Sol                | 13   |\n+-----------------------------+------+";

sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;


typedef vector<int> vi;
typedef pair<int, int> ii;
typedef pair<ii, ii> iiii;

unordered_map<string, int> idToIndex;
string indexToId[275];
string indexToName[275];
int line[275];
int AdjMat[275][275];
vi Transbordos[275][275];
int penalizacion = 60;
int p[275][275];

int AdjMat2[39][39];
vi Transbordos2[39][39];
int p2[39][39];
string supernodos[39];
unordered_map<string, int> sn;
vector<vi> AdjList;
int visited[275];

ii dsn[275];
vector<ii> nearsn;
int AdjMat3[275][275];

void floyd() {
    for (int i = 0; i < 275; i++)
        for (int j = 0; j < 275; j++)
            p[i][j] = i;
    for (int k = 0; k < 275; k++)
        for (int i = 0; i < 275; i++)
            for (int j = 0; j < 275; j++) {
                int time = AdjMat[i][k] + AdjMat[k][j];
                if (!Transbordos[i][k].empty() && !Transbordos[k][j].empty()) {
                    time += Transbordos[i][k][Transbordos[i][k].size()-1] == Transbordos[k][j][0]? 0: penalizacion;
                }
                if (time < AdjMat[i][j]) {
                    AdjMat[i][j] = time;
                    p[i][j] = p[k][j];
                    Transbordos[i][j] = Transbordos[i][k];
                    for (int l = 0; l < Transbordos[k][j].size(); l++) Transbordos[i][j].push_back(Transbordos[k][j][l]);
                }
            }
}

void printPath(int i, int j) {
    if (i != j) printPath(i, p[i][j]);
    cout << " -> " << indexToName[j];
}

void printTime(int time) {
    cout << time/3600 << "h " << (time/60)%60 << "min " << time%60 << "sec" << endl;
}

void dfs(int i, int l, int o) {
    if (visited[i] || !(line[i]>>l%2)) return;
    if (sn.count(indexToId[i])) {
        AdjMat2[o][sn[indexToId[i]]] = AdjMat[idToIndex[supernodos[o]]][i];
        Transbordos2[o][sn[indexToId[i]]].push_back(l);
        return;
    }
    visited[i] = 1;
    for (int j = 0; j < AdjList[i].size(); j++) {
        dfs(AdjList[i][j], l, o);
    }
}

void floyd2() {
    for (int i = 0; i < 39; i++)
        for (int j = 0; j < 39; j++)
            p2[i][j] = i;
    for (int k = 0; k < 39; k++)
        for (int i = 0; i < 39; i++)
            for (int j = 0; j < 39; j++) {
                int time = AdjMat2[i][k] + AdjMat2[k][j];
                if (!Transbordos2[i][k].empty() && !Transbordos2[k][j].empty()) {
                    time += Transbordos2[i][k][Transbordos2[i][k].size()-1] == Transbordos2[k][j][0]? 0: penalizacion;
                }
                if (time < AdjMat2[i][j]) {
                    AdjMat2[i][j] = time;
                    p2[i][j] = p2[k][j];
                    Transbordos2[i][j] = Transbordos2[i][k];
                    for (int l = 0; l < Transbordos2[k][j].size(); l++) Transbordos2[i][j].push_back(Transbordos2[k][j][l]);
                }
            }
}

void printPath2(int i, int j) {
    if (i != j) printPath2(i, p2[i][j]);
    cout << " -> " << indexToName[idToIndex[supernodos[j]]];
}

void dist(int i, int o, int acum) {
    if (visited[i]) return;
    if (sn.count(indexToId[i])) {
        if (nearsn[o].first == -1) {
            nearsn[o].first = sn[indexToId[i]];
            dsn[o].first = acum;
        }
        else {
            nearsn[o].second = sn[indexToId[i]];
            dsn[o].second = acum;
        }
        return;
    }
    visited[i] = 1;
    AdjMat3[o][i] = acum;
    for (int j = 0; j < AdjList[i].size(); j++) {
        dist(AdjList[i][j], o, acum + AdjMat[i][AdjList[i][j]]);
    }
}

int main() {
    high_resolution_clock::time_point rdt1, rdt2;
    AdjList.assign(275, vi());
    nearsn.assign(275, ii(-1, -1));
    for (int i = 0; i < 275; i++) dsn[i].first = dsn[i].second = 10000000;
    try {
        cout << "Conectando..." << endl;
        rdt1 = high_resolution_clock::now();
        driver = get_driver_instance();
        con = driver->connect("tcp://192.168.1.33:3306", "root", "");
        con->setSchema("Metro");
        rdt2 = high_resolution_clock::now();
        cout << duration_cast<microseconds>(rdt2 - rdt1).count() << endl;

        cout << "Cargando estaciones..." << endl;
        rdt1 = high_resolution_clock::now();
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT id, name FROM Stations");
        int i = 0;
        while (res->next()) {
            idToIndex[res->getString("id")] = i;
            indexToId[i] = res->getString("id");
            indexToName[i] = res->getString("name");
            i++;
        }
        delete res;
        rdt2 = high_resolution_clock::now();
        cout << duration_cast<microseconds>(rdt2 - rdt1).count() << endl;

        cout << "Cargando líneas..." << endl;
        rdt1 = high_resolution_clock::now();
        res = stmt->executeQuery("SELECT id, line FROM Line");
        for (i = 0; i < 275; i++) line[i] = 1; //bit 0 enmascara todo XD
        while (res->next()) {
            line[idToIndex[res->getString("id")]] |= (1 << atoi(res->getString("line").c_str()));
        }
        delete res;
        rdt2 = high_resolution_clock::now();
        cout << duration_cast<microseconds>(rdt2 - rdt1).count() << endl;

        cout << "Cargando tiempos..." << endl;
        rdt1 = high_resolution_clock::now();
        for (i = 0; i < 275; i++)
            for(int j = 0; j < 275; j++)
                AdjMat[i][j] = (i == j? 0: 100000); //Tiempo que se tarda en llegar de Vallecas a Ponferrada por la línea 1.
        res = stmt->executeQuery("SELECT id1, id2, Tiempo FROM Trayectos WHERE Estaciones = 1");
        while (res->next()) {
            AdjMat[idToIndex[res->getString("id1")]][idToIndex[res->getString("id2")]] = atoi(res->getString("Tiempo").c_str()) - 50; //Magic number
            int l1 = line[idToIndex[res->getString("id1")]], l2 = line[idToIndex[res->getString("id2")]];
            for (i = 1; i <= 16; i++) {
                if ((l1 >> i)%2 && (l2 >> i)%2) {
                    Transbordos[idToIndex[res->getString("id1")]][idToIndex[res->getString("id2")]].push_back(i);
                    break;
                }
            }
        }
        delete res;
        rdt2 = high_resolution_clock::now();
        cout << duration_cast<microseconds>(rdt2 - rdt1).count() << endl;

        cout << "Floyd I!!!" << endl;
        rdt1 = high_resolution_clock::now();
        floyd();
        rdt2 = high_resolution_clock::now();
        cout << duration_cast<microseconds>(rdt2 - rdt1).count() << endl;

        cout << "Lista de adyacencia" << endl;
        rdt1 = high_resolution_clock::now();
        for (i = 0; i < 275; i++) {
            res = stmt->executeQuery("SELECT ID2 FROM Trayectos WHERE Estaciones = 1 AND ID1 = " + indexToId[i]);
            while (res->next()) {
                AdjList[i].push_back(idToIndex[res->getString("id2")]);
            }
            delete res;
        }
        rdt2 = high_resolution_clock::now();
        cout << duration_cast<microseconds>(rdt2 - rdt1).count() << endl;

        cout << "Supernodos" << endl;
        rdt1 = high_resolution_clock::now();
        res = stmt->executeQuery("SELECT id FROM Supernodos"); //("SELECT id FROM Stations WHERE (SELECT COUNT(*) FROM Line WHERE Stations.id = Line.id)>1");
        i = 0;
        while (res->next()) {
            supernodos[i] = res->getString("id");
            sn[res->getString("id")] = i;
            i++;
        }
        delete res;
        rdt2 = high_resolution_clock::now();
        cout << duration_cast<microseconds>(rdt2 - rdt1).count() << endl;

        cout << "Floyd II!!!" << endl;
        rdt1 = high_resolution_clock::now();
        for (i = 0; i < 39; i++)
            for(int j = 0; j < 39; j++)
                AdjMat2[i][j] = (i == j? 0: 100000);

        for (i = 0; i < 39; i++) {
            for (int l = 1; l <= 16; l++) {
                for (int h = 0; h < 275; h++) visited[h] = 0;
                visited[idToIndex[supernodos[i]]] = 1;
                for (int j = 0; j < AdjList[idToIndex[supernodos[i]]].size(); j++) {
                    dfs(AdjList[idToIndex[supernodos[i]]][j], l, i);
                }
            }
        }
        floyd2();
        for (int i = 0; i < 275; i++) {
            if (!sn.count(indexToId[i])) {
                for (int h = 0; h < 275; h++) visited[h] = 0;
                dist(i, i, 0);
            }
        }
        rdt2 = high_resolution_clock::now();
        cout << duration_cast<microseconds>(rdt2 - rdt1).count() << endl;
        cout << "Listo." << endl;

        delete stmt;
        delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    bool stop = false;
    while (!stop) {
        string op;
        cout << "0: Salir 1: Trayecto 2: Ayuda 3: Supernodos... ";
        cin >> op;
        if(op == "0") stop = true;
        if(op == "1") {
            string id1, id2;
            cout << "Id1: ";
            cin >> id1;
            cout << "Id2: ";
            cin >> id2;
            if (idToIndex.count(id1) && idToIndex.count(id2)) {
                printPath(idToIndex[id1], idToIndex[id2]);
                cout << endl;
                int time = AdjMat[idToIndex[id1]][idToIndex[id2]];
                printTime(time);
                for (int j = 0; j < Transbordos[idToIndex[id1]][ idToIndex[id2]].size(); j++) {
                    cout << Transbordos[idToIndex[id1]][idToIndex[id2]][j] << " ";
                }
                cout << endl;
            } else cout << "Estaciones no registradas" << endl;
        }
        if(op == "2") cout << help;
        if(op == "3") {
            string id1, id2;
            cout << "Id1: ";
            cin >> id1;
            cout << "Id2: ";
            cin >> id2;
            if (idToIndex.count(id1) && idToIndex.count(id2)) {
                if (sn.count(id1) && sn.count(id2)) {
                    printPath2(sn[id1], sn[id2]);
                    cout << endl;
                    printTime(AdjMat2[sn[id1]][sn[id2]]);
                } else if (sn.count(id1)) {
                    int t1 = dsn[idToIndex[id2]].first + AdjMat2[sn[id1]][nearsn[idToIndex[id2]].first];
                    int t2 = dsn[idToIndex[id2]].second + (nearsn[idToIndex[id2]].second != -1? AdjMat2[sn[id1]][nearsn[idToIndex[id2]].second]: 0);

                    if (t1 < t2 && t1 < 100000) {
                        printPath2(sn[id1], nearsn[idToIndex[id2]].first);
                        cout << endl;
                        printTime(t1);
                    } else if (t2 < 100000) {
                        printPath2(sn[id1], nearsn[idToIndex[id2]].second);
                        cout << endl;
                        printTime(t2);
                    } else cout << "Sin camino" << endl;

                } else if (sn.count(id2)) {
                    int t1 = dsn[idToIndex[id1]].first + AdjMat2[nearsn[idToIndex[id1]].first][sn[id2]];
                    int t2 = dsn[idToIndex[id1]].second + (nearsn[idToIndex[id1]].second != -1? AdjMat2[nearsn[idToIndex[id1]].second][sn[id2]]: 0);

                    if (t1 < t2 && t1 < 100000) {
                        printPath2(nearsn[idToIndex[id1]].first, sn[id2]);
                        cout << endl;
                        printTime(t1);
                    } else if (t2 < 100000) {
                        printPath2(nearsn[idToIndex[id1]].second, sn[id2]);
                        cout << endl;
                        printTime(t2);
                    } else cout << "Sin camino" << endl;

                } else {
                    //1 1, 1 2, 2 1, 2 2 y dfs
                    if ((nearsn[idToIndex[id1]].first == nearsn[idToIndex[id2]].first && nearsn[idToIndex[id1]].second == nearsn[idToIndex[id2]].second) ||
                        (nearsn[idToIndex[id1]].first == nearsn[idToIndex[id2]].second && nearsn[idToIndex[id1]].second == nearsn[idToIndex[id2]].first)) {
                            cout << "Mismo tramo" << endl;
                            printTime(AdjMat3[idToIndex[id1]][idToIndex[id2]]);
                    } else {
                        int t11 = dsn[idToIndex[id1]].first + AdjMat2[nearsn[idToIndex[id1]].first][nearsn[idToIndex[id2]].first] + dsn[idToIndex[id2]].first;
                        int t12 = dsn[idToIndex[id1]].first + (nearsn[idToIndex[id2]].second != -1? AdjMat2[nearsn[idToIndex[id1]].first][nearsn[idToIndex[id2]].second]: 0) + dsn[idToIndex[id2]].second;
                        int t21 = dsn[idToIndex[id1]].second + (nearsn[idToIndex[id1]].second != -1? AdjMat2[nearsn[idToIndex[id1]].second][nearsn[idToIndex[id2]].first]: 0) + dsn[idToIndex[id2]].first;
                        int t22 = dsn[idToIndex[id1]].second + (nearsn[idToIndex[id1]].second != -1 && nearsn[idToIndex[id1]].second != -1? AdjMat2[nearsn[idToIndex[id1]].second][nearsn[idToIndex[id2]].second]: 0) + dsn[idToIndex[id2]].second;
                        int t = min(min(t11, t12), min(t21, t22));
                        if (t11 == t) {
                            printPath2(nearsn[idToIndex[id1]].first, nearsn[idToIndex[id2]].first);
                            cout << endl;
                            printTime(t11);
                        } else if (t12 == t) {
                            printPath2(nearsn[idToIndex[id1]].first, nearsn[idToIndex[id2]].second);
                            cout << endl;
                            printTime(t12);
                        } else if (t21 == t) {
                            printPath2(nearsn[idToIndex[id1]].second, nearsn[idToIndex[id2]].first);
                            cout << endl;
                            printTime(t21);
                        } else if (t22 == t) {
                            printPath2(nearsn[idToIndex[id1]].second, nearsn[idToIndex[id2]].second);
                            cout << endl;
                            printTime(t22);
                        } else cout << "Sin camino" << endl;
                    }
                }
            } else cout << "Estaciones no registradas" << endl;
        }
        cout << endl;
    }
    return 0;
}
