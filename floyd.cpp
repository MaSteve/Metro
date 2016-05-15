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
using namespace std;
string help = "+------+-----------------------------+\n| id   | name                        |\n+------+-----------------------------+\n| 1    | Chamartín                   |\n| 10   | Bilbao                      |\n| 1001 | Fuencarral                  |\n| 1002 | Begoña                      |\n| 1005 | Cuzco                       |\n| 1006 | Santiago Bernabéu           |\n| 1013 | Lago                        |\n| 1014 | Batán                       |\n| 1016 | Colonia Jardín              |\n| 1018 | Aviación Española           |\n| 1019 | Cuatro Vientos              |\n| 1020 | Joaquín Vilumbrales         |\n| 1021 | Puerta del Sur              |\n| 1051 | Tres Olivos                 |\n| 1052 | Montecarmelo                |\n| 1053 | Las Tablas                  |\n| 1054 | Ronda de la Comunicación    |\n| 1055 | La Granja                   |\n| 1056 | La Moraleja                 |\n| 1057 | Marqués de la Valdavia      |\n| 1058 | Manuel de Falla             |\n| 1059 | Baunatal                    |\n| 1060 | Reyes Católicos             |\n| 1061 | Hospital Infanta Sofía      |\n| 11   | Tribunal                    |\n| 1102 | Abrantes                    |\n| 1103 | Pan Bendito                 |\n| 1104 | San Francisco               |\n| 1105 | Carabanchel Alto            |\n| 1106 | La Peseta                   |\n| 1107 | La Fortuna                  |\n| 12   | Gran Vía                    |\n| 1202 | Parque Lisboa               |\n| 1203 | Alcorcón Central            |\n| 1204 | Parque Oeste                |\n| 1205 | Universidad Rey Juan Carlos |\n| 1206 | Móstoles Central            |\n| 1207 | Pradillo                    |\n| 1208 | Hospital de Móstoles        |\n| 1209 | Manuela Malasaña            |\n| 1210 | Loranca                     |\n| 1212 | Hospital de Fuenlabrada     |\n| 1213 | Parque Europa               |\n| 1214 | Fuenlabrada Central         |\n| 1215 | Parque de los Estados       |\n| 1217 | Arroyo Culebro              |\n| 1218 | Conservatorio               |\n| 1219 | Alonso de Mendoza           |\n| 1220 | Getafe Central              |\n| 1221 | Juan de la Cierva           |\n| 1222 | El Casar                    |\n| 1223 | Los Espartales              |\n| 1224 | El Bercial                  |\n| 1225 | El Carrascal                |\n| 1226 | Julián Besteiro             |\n| 1227 | Casa del Reloj              |\n| 1228 | Hospital Severo Ochoa       |\n| 1229 | Leganés Central             |\n| 1230 | San Nicasio                 |\n| 128  | La Gavia                    |\n| 129  | Las Suertes                 |\n| 13   | Vodafone Sol                |\n| 130  | Valdecarros                 |\n| 14   | Tirso de Molina             |\n| 15   | Antón Martín                |\n| 152  | Bambú                       |\n| 153  | Pinar de Chamartín          |\n| 16   | Atocha                      |\n| 17   | Atocha Renfe                |\n| 18   | Menéndez Pelayo             |\n| 19   | Pacífico                    |\n| 2    | Plaza de Castilla           |\n| 20   | Puente de Vallecas          |\n| 21   | Nueva Numancia              |\n| 22   | Portazgo                    |\n| 23   | Buenos Aires                |\n| 24   | Alto del Arenal             |\n| 25   | Miguel Hernández            |\n| 252  | La Almudena                 |\n| 253  | Alsacia                     |\n| 254  | Avenida de Guadalajara      |\n| 255  | Las Rosas                   |\n| 26   | Sierra de Guadalupe         |\n| 27   | Villa de Vallecas           |\n| 28   | Congosto                    |\n| 29   | La Elipa                    |\n| 3    | Valdeacederas               |\n| 30   | Ventas                      |\n| 301  | Legazpi                     |\n| 302  | Delicias                    |\n| 303  | Palos de la Frontera        |\n| 304  | Embajadores                 |\n| 305  | Lavapiés                    |\n| 307  | Callao                      |\n| 308  | Plaza de España             |\n| 309  | Ventura Rodríguez           |\n| 31   | Manuel Becerra              |\n| 310  | Argüelles                   |\n| 311  | Moncloa                     |\n| 3124 | Almendrales                 |\n| 32   | Goya                        |\n| 33   | Príncipe de Vergara         |\n| 34   | Retiro                      |\n| 35   | Banco de España             |\n| 352  | Hospital 12 de Octubre      |\n| 353  | San Fermín - Orcasur        |\n| 354  | Ciudad de los Ángeles       |\n| 355  | Villaverde Bajo Cruce       |\n| 356  | San Cristóbal               |\n| 357  | Villaverde Alto             |\n| 36   | Sevilla                     |\n| 37   | Ópera                       |\n| 38   | Santo Domingo               |\n| 39   | Noviciado                   |\n| 4    | Tetuán                      |\n| 40   | San Bernardo                |\n| 404  | Alonso Martínez             |\n| 405  | Colón                       |\n| 406  | Serrano                     |\n| 407  | Velázquez                   |\n| 409  | Lista                       |\n| 41   | Quevedo                     |\n| 410  | Diego de León               |\n| 411  | Avenida de América          |\n| 412  | Prosperidad                 |\n| 413  | Alfonso XIII                |\n| 414  | Avenida de la Paz           |\n| 415  | Arturo Soria                |\n| 416  | Esperanza                   |\n| 417  | Canillas                    |\n| 418  | Mar de Cristal              |\n| 419  | San Lorenzo                 |\n| 42   | Canal                       |\n| 420  | Parque de Santa María       |\n| 421  | Hortaleza                   |\n| 422  | Manoteras                   |\n| 5    | Estrecho                    |\n| 501  | Canillejas                  |\n| 502  | Torre Arias                 |\n| 503  | Suanzes                     |\n| 504  | Ciudad Lineal               |\n| 505  | Pueblo Nuevo                |\n| 506  | Quintana                    |\n| 507  | El Carmen                   |\n| 510  | Núñez de Balboa             |\n| 511  | Rubén Darío                 |\n| 5112 | Fuente de la Mora           |\n| 5113 | Virgen del Cortijo          |\n| 5114 | Antonio Saura               |\n| 5115 | Álvarez de Villaamil        |\n| 5116 | Blasco Ibáñez               |\n| 5117 | María Tudor                 |\n| 5118 | Palas de Rey                |\n| 513  | Chueca                      |\n| 517  | La Latina                   |\n| 518  | Puerta de Toledo            |\n| 519  | Acacias                     |\n| 520  | Pirámides                   |\n| 521  | Marqués de Vadillo          |\n| 5212 | Prado de la Vega            |\n| 5213 | Colonia de los Ángeles      |\n| 5214 | Prado del Rey               |\n| 5215 | Somosaguas Sur              |\n| 5216 | Somosaguas Centro           |\n| 5217 | Pozuelo Oeste               |\n| 5219 | Bélgica                     |\n| 522  | Urgel                       |\n| 5220 | Dos Castillas               |\n| 5221 | Campus de Somosaguas        |\n| 5222 | Avenida de Europa           |\n| 5223 | Berna                       |\n| 5224 | Estación de Aravaca         |\n| 523  | Oporto                      |\n| 524  | Vista Alegre                |\n| 525  | Carabanchel                 |\n| 526  | Eugenia de Montijo          |\n| 527  | Aluche                      |\n| 528  | Empalme                     |\n| 529  | Campamento                  |\n| 530  | Casa de Campo               |\n| 5312 | Ciudad de la Imagen         |\n| 5313 | José Isbert                 |\n| 5314 | Ciudad del Cine             |\n| 5315 | Cocheras                    |\n| 5316 | Retamares                   |\n| 5318 | Montepríncipe               |\n| 5319 | Ventorro del Cano           |\n| 5320 | Prado del Espino            |\n| 5322 | Cantabria                   |\n| 5324 | Ferial de Boadilla          |\n| 5325 | Boadilla Centro             |\n| 5326 | Nuevo Mundo                 |\n| 5327 | Siglo XXI                   |\n| 5328 | Infante Don Luís            |\n| 5329 | Puerta de Boadilla          |\n| 551  | El Capricho                 |\n| 552  | Alameda de Osuna            |\n| 6    | Alvarado                    |\n| 601  | Laguna                      |\n| 602  | Carpetana                   |\n| 604  | Opañel                      |\n| 605  | Plaza Elíptica              |\n| 606  | Usera                       |\n| 608  | Arganzuela - Planetario     |\n| 609  | Méndez Álvaro               |\n| 611  | Conde de Casal              |\n| 612  | Sainz de Baranda            |\n| 613  | O'Donnell                   |\n| 617  | República Argentina         |\n| 618  | Nuevos Ministerios          |\n| 620  | Guzmán el Bueno             |\n| 621  | Metropolitano               |\n| 622  | Ciudad Universitaria        |\n| 625  | Principe Pío                |\n| 626  | Puerta del Ángel            |\n| 627  | Alto de Extremadura         |\n| 628  | Lucero                      |\n| 7    | Cuatro Caminos              |\n| 701  | Las Musas                   |\n| 702  | San Blas                    |\n| 703  | Simancas                    |\n| 704  | García Noblejas             |\n| 705  | Ascao                       |\n| 707  | Barrio de la Concepción     |\n| 708  | Parque de las Avenidas      |\n| 709  | Cartagena                   |\n| 711  | Gregorio Marañón            |\n| 712  | Alonso Cano                 |\n| 714  | Islas Filipinas             |\n| 716  | Francos Rodríguez           |\n| 717  | Valdezarza                  |\n| 718  | Antonio Machado             |\n| 719  | Peñagrande                  |\n| 720  | Avenida de la Ilustración   |\n| 721  | Lacoma                      |\n| 723  | Pitis                       |\n| 751  | Estadio Olímpico            |\n| 754  | Barrio del Puerto           |\n| 755  | Coslada Central             |\n| 756  | La Rambla                   |\n| 757  | San Fernando                |\n| 758  | Jarama                      |\n| 759  | Henares                     |\n| 760  | Hospital del Henares        |\n| 8    | Ríos Rosas                  |\n| 802  | Colombia                    |\n| 803  | Pinar del Rey               |\n| 805  | Campo de las Naciones       |\n| 806  | Aeropuerto T1 T2 T3         |\n| 807  | Barajas                     |\n| 808  | Aeropuerto T4               |\n| 9    | Iglesia                     |\n| 901  | Herrera Oria                |\n| 902  | Barrio del Pilar            |\n| 903  | Ventilla                    |\n| 905  | Duque de Pastrana           |\n| 906  | Pío XII                     |\n| 908  | Concha Espina               |\n| 909  | Cruz del Rayo               |\n| 913  | Ibiza                       |\n| 915  | Estrella                    |\n| 916  | Vinateros                   |\n| 917  | Artilleros                  |\n| 918  | Pavones                     |\n| 919  | Valdebernardo               |\n| 920  | Vicálvaro                   |\n| 921  | San Cipriano                |\n| 922  | Puerta de Arganda           |\n| 924  | Rivas Urbanizaciones        |\n| 925  | Rivas Futura                |\n| 926  | Rivas Vaciamadrid           |\n| 927  | La Poveda                   |\n| 928  | Arganda del Rey             |\n| 951  | Mirasierra                  |\n| 952  | Paco de Lucía               |\n+------+-----------------------------+";


typedef vector<int> vi;

unordered_map<string, int> idToIndex;
string indexToId[275];
string indexToName[275];
int line[275];
int AdjMat[275][275];
vi Transbordos[275][275];
int penalizacion = 60;
int p[275][275];

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


int main() {
    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;
        sql::ResultSet *res;

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
        for (i = 0; i < 275; i++) line[i] = 0;
        while (res->next()) {
            line[idToIndex[res->getString("id")]] |= (1 << atoi(res->getString("line").c_str()));
        }
        delete res;

        cout << "Cargando tiempos..." << endl;
        for (i = 0; i < 275; i++)
            for(int j = 0; j < 275; j++)
                AdjMat[i][j] = 100000; //Tiempo que se tarda en llegar de Vallecas a Ponferrada por la línea 1.
        res = stmt->executeQuery("SELECT id1, id2, Tiempo FROM Trayectos WHERE Estaciones = 1");
        while (res->next()) {
            AdjMat[idToIndex[res->getString("id1")]][idToIndex[res->getString("id2")]] = atoi(res->getString("Tiempo").c_str()) - 50; //Magic number
            int l1 = line[idToIndex[res->getString("id1")]], l2 = line[idToIndex[res->getString("id2")]];
            for (i = 1; i <= 16; i++) {
                if ((l1 >> i)%2 == (l2 >> i)%2) {
                    Transbordos[idToIndex[res->getString("id1")]][idToIndex[res->getString("id2")]].push_back(i);
                    break;
                }
            }
        }
        cout << "Floyd!!!" << endl;
        floyd();
        cout << "Listo." << endl;

        delete res;
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
        cout << "0: Salir 1: Trayecto 2: Ayuda... ";
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
            } else cout << "Estaciones no registradas" << endl;
        }
        if(op == "2") cout << help;
        cout << endl;
    }
    return 0;
}
