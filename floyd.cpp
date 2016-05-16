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
using namespace std;
string help = "+------+-----------------------------+\n| id   | name                        |\n+------+-----------------------------+\n| 1    | Chamartín                   |\n| 10   | Bilbao                      |\n| 1001 | Fuencarral                  |\n| 1002 | Begoña                      |\n| 1005 | Cuzco                       |\n| 1006 | Santiago Bernabéu           |\n| 1013 | Lago                        |\n| 1014 | Batán                       |\n| 1016 | Colonia Jardín              |\n| 1018 | Aviación Española           |\n| 1019 | Cuatro Vientos              |\n| 1020 | Joaquín Vilumbrales         |\n| 1021 | Puerta del Sur              |\n| 1051 | Tres Olivos                 |\n| 1052 | Montecarmelo                |\n| 1053 | Las Tablas                  |\n| 1054 | Ronda de la Comunicación    |\n| 1055 | La Granja                   |\n| 1056 | La Moraleja                 |\n| 1057 | Marqués de la Valdavia      |\n| 1058 | Manuel de Falla             |\n| 1059 | Baunatal                    |\n| 1060 | Reyes Católicos             |\n| 1061 | Hospital Infanta Sofía      |\n| 11   | Tribunal                    |\n| 1102 | Abrantes                    |\n| 1103 | Pan Bendito                 |\n| 1104 | San Francisco               |\n| 1105 | Carabanchel Alto            |\n| 1106 | La Peseta                   |\n| 1107 | La Fortuna                  |\n| 12   | Gran Vía                    |\n| 1202 | Parque Lisboa               |\n| 1203 | Alcorcón Central            |\n| 1204 | Parque Oeste                |\n| 1205 | Universidad Rey Juan Carlos |\n| 1206 | Móstoles Central            |\n| 1207 | Pradillo                    |\n| 1208 | Hospital de Móstoles        |\n| 1209 | Manuela Malasaña            |\n| 1210 | Loranca                     |\n| 1212 | Hospital de Fuenlabrada     |\n| 1213 | Parque Europa               |\n| 1214 | Fuenlabrada Central         |\n| 1215 | Parque de los Estados       |\n| 1217 | Arroyo Culebro              |\n| 1218 | Conservatorio               |\n| 1219 | Alonso de Mendoza           |\n| 1220 | Getafe Central              |\n| 1221 | Juan de la Cierva           |\n| 1222 | El Casar                    |\n| 1223 | Los Espartales              |\n| 1224 | El Bercial                  |\n| 1225 | El Carrascal                |\n| 1226 | Julián Besteiro             |\n| 1227 | Casa del Reloj              |\n| 1228 | Hospital Severo Ochoa       |\n| 1229 | Leganés Central             |\n| 1230 | San Nicasio                 |\n| 128  | La Gavia                    |\n| 129  | Las Suertes                 |\n| 13   | Vodafone Sol                |\n| 130  | Valdecarros                 |\n| 14   | Tirso de Molina             |\n| 15   | Antón Martín                |\n| 152  | Bambú                       |\n| 153  | Pinar de Chamartín          |\n| 16   | Atocha                      |\n| 17   | Atocha Renfe                |\n| 18   | Menéndez Pelayo             |\n| 19   | Pacífico                    |\n| 2    | Plaza de Castilla           |\n| 20   | Puente de Vallecas          |\n| 21   | Nueva Numancia              |\n| 22   | Portazgo                    |\n| 23   | Buenos Aires                |\n| 24   | Alto del Arenal             |\n| 25   | Miguel Hernández            |\n| 252  | La Almudena                 |\n| 253  | Alsacia                     |\n| 254  | Avenida de Guadalajara      |\n| 255  | Las Rosas                   |\n| 26   | Sierra de Guadalupe         |\n| 27   | Villa de Vallecas           |\n| 28   | Congosto                    |\n| 29   | La Elipa                    |\n| 3    | Valdeacederas               |\n| 30   | Ventas                      |\n| 301  | Legazpi                     |\n| 302  | Delicias                    |\n| 303  | Palos de la Frontera        |\n| 304  | Embajadores                 |\n| 305  | Lavapiés                    |\n| 307  | Callao                      |\n| 308  | Plaza de España             |\n| 309  | Ventura Rodríguez           |\n| 31   | Manuel Becerra              |\n| 310  | Argüelles                   |\n| 311  | Moncloa                     |\n| 3124 | Almendrales                 |\n| 32   | Goya                        |\n| 33   | Príncipe de Vergara         |\n| 34   | Retiro                      |\n| 35   | Banco de España             |\n| 352  | Hospital 12 de Octubre      |\n| 353  | San Fermín - Orcasur        |\n| 354  | Ciudad de los Ángeles       |\n| 355  | Villaverde Bajo Cruce       |\n| 356  | San Cristóbal               |\n| 357  | Villaverde Alto             |\n| 36   | Sevilla                     |\n| 37   | Ópera                       |\n| 38   | Santo Domingo               |\n| 39   | Noviciado                   |\n| 4    | Tetuán                      |\n| 40   | San Bernardo                |\n| 404  | Alonso Martínez             |\n| 405  | Colón                       |\n| 406  | Serrano                     |\n| 407  | Velázquez                   |\n| 409  | Lista                       |\n| 41   | Quevedo                     |\n| 410  | Diego de León               |\n| 411  | Avenida de América          |\n| 412  | Prosperidad                 |\n| 413  | Alfonso XIII                |\n| 414  | Avenida de la Paz           |\n| 415  | Arturo Soria                |\n| 416  | Esperanza                   |\n| 417  | Canillas                    |\n| 418  | Mar de Cristal              |\n| 419  | San Lorenzo                 |\n| 42   | Canal                       |\n| 420  | Parque de Santa María       |\n| 421  | Hortaleza                   |\n| 422  | Manoteras                   |\n| 5    | Estrecho                    |\n| 501  | Canillejas                  |\n| 502  | Torre Arias                 |\n| 503  | Suanzes                     |\n| 504  | Ciudad Lineal               |\n| 505  | Pueblo Nuevo                |\n| 506  | Quintana                    |\n| 507  | El Carmen                   |\n| 510  | Núñez de Balboa             |\n| 511  | Rubén Darío                 |\n| 5112 | Fuente de la Mora           |\n| 5113 | Virgen del Cortijo          |\n| 5114 | Antonio Saura               |\n| 5115 | Álvarez de Villaamil        |\n| 5116 | Blasco Ibáñez               |\n| 5117 | María Tudor                 |\n| 5118 | Palas de Rey                |\n| 513  | Chueca                      |\n| 517  | La Latina                   |\n| 518  | Puerta de Toledo            |\n| 519  | Acacias                     |\n| 520  | Pirámides                   |\n| 521  | Marqués de Vadillo          |\n| 5212 | Prado de la Vega            |\n| 5213 | Colonia de los Ángeles      |\n| 5214 | Prado del Rey               |\n| 5215 | Somosaguas Sur              |\n| 5216 | Somosaguas Centro           |\n| 5217 | Pozuelo Oeste               |\n| 5219 | Bélgica                     |\n| 522  | Urgel                       |\n| 5220 | Dos Castillas               |\n| 5221 | Campus de Somosaguas        |\n| 5222 | Avenida de Europa           |\n| 5223 | Berna                       |\n| 5224 | Estación de Aravaca         |\n| 523  | Oporto                      |\n| 524  | Vista Alegre                |\n| 525  | Carabanchel                 |\n| 526  | Eugenia de Montijo          |\n| 527  | Aluche                      |\n| 528  | Empalme                     |\n| 529  | Campamento                  |\n| 530  | Casa de Campo               |\n| 5312 | Ciudad de la Imagen         |\n| 5313 | José Isbert                 |\n| 5314 | Ciudad del Cine             |\n| 5315 | Cocheras                    |\n| 5316 | Retamares                   |\n| 5318 | Montepríncipe               |\n| 5319 | Ventorro del Cano           |\n| 5320 | Prado del Espino            |\n| 5322 | Cantabria                   |\n| 5324 | Ferial de Boadilla          |\n| 5325 | Boadilla Centro             |\n| 5326 | Nuevo Mundo                 |\n| 5327 | Siglo XXI                   |\n| 5328 | Infante Don Luís            |\n| 5329 | Puerta de Boadilla          |\n| 551  | El Capricho                 |\n| 552  | Alameda de Osuna            |\n| 6    | Alvarado                    |\n| 601  | Laguna                      |\n| 602  | Carpetana                   |\n| 604  | Opañel                      |\n| 605  | Plaza Elíptica              |\n| 606  | Usera                       |\n| 608  | Arganzuela - Planetario     |\n| 609  | Méndez Álvaro               |\n| 611  | Conde de Casal              |\n| 612  | Sainz de Baranda            |\n| 613  | O'Donnell                   |\n| 617  | República Argentina         |\n| 618  | Nuevos Ministerios          |\n| 620  | Guzmán el Bueno             |\n| 621  | Metropolitano               |\n| 622  | Ciudad Universitaria        |\n| 625  | Principe Pío                |\n| 626  | Puerta del Ángel            |\n| 627  | Alto de Extremadura         |\n| 628  | Lucero                      |\n| 7    | Cuatro Caminos              |\n| 701  | Las Musas                   |\n| 702  | San Blas                    |\n| 703  | Simancas                    |\n| 704  | García Noblejas             |\n| 705  | Ascao                       |\n| 707  | Barrio de la Concepción     |\n| 708  | Parque de las Avenidas      |\n| 709  | Cartagena                   |\n| 711  | Gregorio Marañón            |\n| 712  | Alonso Cano                 |\n| 714  | Islas Filipinas             |\n| 716  | Francos Rodríguez           |\n| 717  | Valdezarza                  |\n| 718  | Antonio Machado             |\n| 719  | Peñagrande                  |\n| 720  | Avenida de la Ilustración   |\n| 721  | Lacoma                      |\n| 723  | Pitis                       |\n| 751  | Estadio Olímpico            |\n| 754  | Barrio del Puerto           |\n| 755  | Coslada Central             |\n| 756  | La Rambla                   |\n| 757  | San Fernando                |\n| 758  | Jarama                      |\n| 759  | Henares                     |\n| 760  | Hospital del Henares        |\n| 8    | Ríos Rosas                  |\n| 802  | Colombia                    |\n| 803  | Pinar del Rey               |\n| 805  | Campo de las Naciones       |\n| 806  | Aeropuerto T1 T2 T3         |\n| 807  | Barajas                     |\n| 808  | Aeropuerto T4               |\n| 9    | Iglesia                     |\n| 901  | Herrera Oria                |\n| 902  | Barrio del Pilar            |\n| 903  | Ventilla                    |\n| 905  | Duque de Pastrana           |\n| 906  | Pío XII                     |\n| 908  | Concha Espina               |\n| 909  | Cruz del Rayo               |\n| 913  | Ibiza                       |\n| 915  | Estrella                    |\n| 916  | Vinateros                   |\n| 917  | Artilleros                  |\n| 918  | Pavones                     |\n| 919  | Valdebernardo               |\n| 920  | Vicálvaro                   |\n| 921  | San Cipriano                |\n| 922  | Puerta de Arganda           |\n| 924  | Rivas Urbanizaciones        |\n| 925  | Rivas Futura                |\n| 926  | Rivas Vaciamadrid           |\n| 927  | La Poveda                   |\n| 928  | Arganda del Rey             |\n| 951  | Mirasierra                  |\n| 952  | Paco de Lucía               |\n+------+-----------------------------+";

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
//int p3[275][275];
vector<ii> nearsn;

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
    for (int j = 0; j < AdjList[i].size(); j++) {
        dist(AdjList[i][j], o, acum + AdjMat[i][AdjList[i][j]]);
    }
}

int main() {
    AdjList.assign(275, vi());
    nearsn.assign(275, ii(-1, -1));
    for (int i = 0; i < 275; i++) dsn[i].first = dsn[i].second = 10000000;
    try {
        cout << "Conectando..." << endl;
        driver = get_driver_instance();
        con = driver->connect("tcp://192.168.1.33:3306", "root", "");
        con->setSchema("Metro");

        cout << "Cargando estaciones..." << endl;
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT id FROM Stations");
        int i = 0;
        while (res->next()) {
            //cout << res->getString("user") << endl;
            idToIndex[res->getString(1)] = i;
            indexToId[i] = res->getString(1);
            i++;
        }
        delete res;

        res = stmt->executeQuery("SELECT id, name FROM Stations");
        while (res->next()) {
            indexToName[idToIndex[res->getString("id")]] = res->getString("name");
        }
        delete res;

        cout << "Cargando líneas..." << endl;
        res = stmt->executeQuery("SELECT id, line FROM Line");
        for (i = 0; i < 275; i++) line[i] = 1; //bit 0 enmascara todo XD
        while (res->next()) {
            line[idToIndex[res->getString("id")]] |= (1 << atoi(res->getString("line").c_str()));
        }
        delete res;
        /*for (i = 0; i < 275; i++) cout << line[i] << " ";
        cout << endl;*/

        cout << "Cargando tiempos..." << endl;
        for (i = 0; i < 275; i++)
            for(int j = 0; j < 275; j++)
                AdjMat[i][j] = 100000; //Tiempo que se tarda en llegar de Vallecas a Ponferrada por la línea 1.
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
        cout << "Floyd!!!" << endl;
        floyd();
        cout << "Listo." << endl;


        for (i = 0; i < 275; i++) {
            //cout << "T:" << i << endl;
            res = stmt->executeQuery("SELECT ID2 FROM Trayectos WHERE Estaciones = 1 AND ID1 = " + indexToId[i]);
            while (res->next()) {
                AdjList[i].push_back(idToIndex[res->getString("id2")]);
                //AdjList[idToIndex[res->getString("id2")]].push_back(i);
                //cout << res->getString("id2") << " ";
            }
            //cout << endl;
            delete res;
        }

        res = stmt->executeQuery("SELECT id FROM Supernodos");//("SELECT id FROM Stations WHERE (SELECT COUNT(*) FROM Line WHERE Stations.id = Line.id)>1");
        i = 0;
        while (res->next()) {
            supernodos[i] = res->getString("id");
            sn[res->getString("id")] = i;
            i++;
        }
        delete res;

        for (i = 0; i < 39; i++)
            for(int j = 0; j < 39; j++)
                AdjMat2[i][j] = 100000;

        for (i = 0; i < 39; i++) {
            for (int l = 1; l <= 16; l++) {
                for (int h = 0; h < 275; h++) visited[h] = 0;
                visited[idToIndex[supernodos[i]]] = 1;
                for (int j = 0; j < AdjList[idToIndex[supernodos[i]]].size(); j++) {
                    dfs(AdjList[idToIndex[supernodos[i]]][j], l, i);
                }
                //dfs(idToIndex[supernodos[i]],l, i);
            }
        }
        floyd2();
        for (int i = 0; i < 275; i++) {
            if (!sn.count(indexToId[i])) {
                for (int h = 0; h < 275; h++) visited[h] = 0;
                dist(i, i, 0);
            }
        }
        /*for (int i = 0; i < 275; i++) cout << nearsn[i].first << nearsn[i].second << " ";
        cout << endl;*/


        /*for (i = 0; i < 39; i++) {
            for(int j = 0; j < 39; j++) {
                printf("%4d", AdjMat2[i][j]);
                //cout << AdjMat2[i][j] << " ";
            }
            cout << endl;
        }*/

        /*
                string id1 = supernodos[i], id2 = supernodos[j];
                int l1 = line[idToIndex[id1]], l2 = line[idToIndex[id2]];
                for (int l = 1; l <= 16; l++) {
                    if ((l1 >> l)%2 && (l2 >> l)%2) {
                        res = stmt->executeQuery("SELECT Tiempo FROM Trayectos AS T WHERE Tiempo in (SELECT Tiempo FROM Trayectos WHERE id1 = T.id1 AND id2 IN (SELECT id FROM Supernodos) LIMIT 2) AND id1 = "+id1+" AND id2 = "+id2);
                        if (res->next()) {
                            AdjMat2[i][j] = atoi(res->getString("Tiempo").c_str()) - 50;
                            Transbordos[i][j].push_back(l);
                        }
                        delete res;
                    }
                }
            }*/

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
                cout << time/3600 << "h " << (time/60)%60 << "min " << time%60 << "sec" << endl;
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
                    cout << AdjMat2[sn[id1]][sn[id2]] << endl;
                } else if (sn.count(id1)) {
                    //cout << dsn[idToIndex[id2]].first <<  " " << dsn[idToIndex[id2]].second << endl;
                    //cout << nearsn[idToIndex[id2]].first << " " << nearsn[idToIndex[id2]].second << endl;
                    int t1 = dsn[idToIndex[id2]].first + AdjMat2[sn[id1]][nearsn[idToIndex[id2]].first];
                    //cout << t1 << endl;
                    int t2 = dsn[idToIndex[id2]].second + (nearsn[idToIndex[id2]].second != -1? AdjMat2[sn[id1]][nearsn[idToIndex[id2]].second]: 0);
                    //cout << t2 << endl;

                    if (t1 < t2 && t1 < 100000) {
                        //cout << "t3" << t1 << nearsn[idToIndex[id2]].first << endl;
                        printPath2(sn[id1], nearsn[idToIndex[id2]].first);
                        //cout << "t4" << endl;
                        cout << endl << t1 << endl;
                    } else if (t2 < 100000) {
                        //cout << "t5" << t2 << nearsn[idToIndex[id2]].second << endl;
                        printPath2(sn[id1], nearsn[idToIndex[id2]].second);
                        //cout << "t6" << endl;
                        cout << endl << t2 << endl;
                    } else cout << "Sin camino" << endl;

                } else if (sn.count(id2)) {
                    int t1 = dsn[idToIndex[id1]].first + AdjMat2[nearsn[idToIndex[id1]].first][sn[id2]];
                    int t2 = dsn[idToIndex[id1]].second + (nearsn[idToIndex[id1]].second != -1? AdjMat2[nearsn[idToIndex[id1]].second][sn[id2]]: 0);

                    if (t1 < t2 && t1 < 100000) {
                        printPath2(nearsn[idToIndex[id1]].first, sn[id2]);
                        cout << endl << t1 << endl;
                    } else if (t2 < 100000) {
                        printPath2(nearsn[idToIndex[id1]].second, sn[id2]);
                        cout << endl << t2 << endl;
                    } else cout << "Sin camino" << endl;

                } else {
                    //1 1, 1 2, 2 1, 2 2 y dfs
                    if ((nearsn[idToIndex[id1]].first == nearsn[idToIndex[id2]].first && nearsn[idToIndex[id1]].second == nearsn[idToIndex[id2]].second) ||
                        (nearsn[idToIndex[id1]].first == nearsn[idToIndex[id2]].second && nearsn[idToIndex[id1]].second == nearsn[idToIndex[id2]].first)) {
                            cout << "Mismo tramo" << endl;
                            cout << AdjMat[idToIndex[id1]][idToIndex[id2]] << endl;
                    } else {
                        int t11 = dsn[idToIndex[id1]].first + AdjMat2[nearsn[idToIndex[id1]].first][nearsn[idToIndex[id2]].first] + dsn[idToIndex[id2]].first;
                        int t12 = dsn[idToIndex[id1]].first + (nearsn[idToIndex[id2]].second != -1? AdjMat2[nearsn[idToIndex[id1]].first][nearsn[idToIndex[id2]].second]: 0) + dsn[idToIndex[id2]].second;
                        int t21 = dsn[idToIndex[id1]].second + (nearsn[idToIndex[id1]].second != -1? AdjMat2[nearsn[idToIndex[id1]].second][nearsn[idToIndex[id2]].first]: 0) + dsn[idToIndex[id2]].first;
                        int t22 = dsn[idToIndex[id1]].second + (nearsn[idToIndex[id1]].second != -1 && nearsn[idToIndex[id1]].second != -1? AdjMat2[nearsn[idToIndex[id1]].second][nearsn[idToIndex[id2]].second]: 0) + dsn[idToIndex[id2]].second;
                        int t = min(min(t11, t12), min(t21, t22));
                        if (t11 == t) {
                            printPath2(nearsn[idToIndex[id1]].first, nearsn[idToIndex[id2]].first);
                            cout << endl << t11 << endl;
                        } else if (t12 == t) {
                            printPath2(nearsn[idToIndex[id1]].first, nearsn[idToIndex[id2]].second);
                            cout << endl << t12 << endl;
                        } else if (t21 == t) {
                            printPath2(nearsn[idToIndex[id1]].second, nearsn[idToIndex[id2]].first);
                            cout << endl << t21 << endl;
                        } else if (t22 == t) {
                            printPath2(nearsn[idToIndex[id1]].second, nearsn[idToIndex[id2]].second);
                            cout << endl << t22 << endl;
                        } else cout << "Sin camino" << endl;
                    }
                }
            } else cout << "Estaciones no registradas" << endl;
        }
        cout << endl;
    }
    return 0;
}
