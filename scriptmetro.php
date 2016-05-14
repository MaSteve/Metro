<?php
	$servername = "localhost";
	$username = "root";
	$password = "";
	$db = "Metro";

	// Create connection
	$conn = new mysqli($servername, $username, $password);

	// Check connection
	if ($conn->connect_error) die("Connection failed: " . $conn->connect_error);
	else {
		echo "Connected successfully";

		mysqli_select_db($conn, $db);

		$list = mysqli_query($conn, 'SELECT id FROM Stations');
		$list = mysqli_fetch_all($list, MYSQLI_NUM);
		foreach ($list as $key => $value) {
			$list[$key] = $value[0];
		}
		//var_dump($list);

		echo "Script METRO<br>";
		$ch = curl_init();
		$timeout = 10;
		foreach ($list as $id1) {
			foreach ($list as $id2) {
				if ($id1 == $id2) continue;
				echo "T: $id1 $id2"."<br>";
				//$id1 = "1219";
				//$id2 = "1220";
				$url = "http://www.metromadrid.es/metro/Resultado.asp?Simple=1&rbDestino=estacion&rbOrigen=estacion&idOrigen=$id1&idDestino=$id2&numeroOrigen=&numeroDestino=&cmbFechaCalculo=2016/03/22&cmbHora=09&cmbMinutos=01&rbTipoRuta=corta&chkescaleras=&chkmecanicas=&chksilla=&cmbOrigen=&cmbDestino=&btnBuscar.x=&btnBuscar.y=&btnBuscar=Buscar+Trayecto";

				curl_setopt($ch, CURLOPT_URL, $url);
				curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
				curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);
				$html = curl_exec($ch);

				$dom = new DOMDocument();
				@$dom->loadHTML($html);
				
				$stations = $dom->getElementsByTagName('dd')[2]->nodeValue;
				$time = $dom->getElementsByTagName('strong')[2]->nodeValue;

				preg_match('/[0-9]+/', $stations, $match);
				$stations = $match[0];

				preg_match_all('/[0-9]+/', $time, $match);
				$time = intval($match[0][0])*3600 + intval($match[0][1])*60 + intval($match[0][2]);

				//echo $stations;
				//echo $time;
				mysqli_query($conn, "INSERT INTO Trayectos(ID1, ID2, Estaciones, Tiempo) VALUES ($id1, $id2, $stations, $time)");
			}
		}
		curl_close($ch);
	}
?>
