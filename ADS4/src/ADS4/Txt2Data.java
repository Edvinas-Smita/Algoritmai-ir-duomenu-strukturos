package ADS4;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;

public class Txt2Data
{
	public static List<City> read(String input) throws IOException
	{
		BufferedReader inputReader = new BufferedReader(new FileReader(input), 512);
		
		String line;
		String[] subLine;
		int depart, arrive;
		List<City> cities = new FindableList<>();
		while ((line = inputReader.readLine()) != null && !line.startsWith("( ͡° ͜ʖ ͡°)"))
		{
			subLine = line.split("[\040\t:]");
			
			if (subLine.length < 6 || subLine[0].equals(subLine[5]))
			{
				System.out.println("\"" + line + "\" does not contain recognised format");
				continue;
			}
			
			City start = new City(subLine[0]);
			City end = new City(subLine[5]);
			if (!cities.contains(start))
			{
				cities.add(start);
			}
			if (!cities.contains(end))
			{
				cities.add(end);
			}
			
			try
			{
				depart = Integer.parseInt(subLine[1]) * 60 + Integer.parseInt(subLine[2]);
				arrive = Integer.parseInt(subLine[3]) * 60 + Integer.parseInt(subLine[4]);
			}
			catch (Exception e)
			{
				System.out.println("\"" + line + "\" does not contain recognised format");
				continue;
			}
			//System.out.println(subLine[0] + "|" + depart + "|" + arrive + "|" + subLine[5]);
			((FindableList<City>) cities).find(start).linkWith(((FindableList<City>) cities).find(end), depart, arrive);
		}
		//cities.forEach(city -> city.printLinks());
		//System.out.println("---------------------------------------------------------------");
		//System.out.println(City.fly(((FindableList<City>) cities).find(new City("A")), ((FindableList<City>) cities).find(new City("D"))));
		inputReader.close();
		
		return cities;
	}
}
