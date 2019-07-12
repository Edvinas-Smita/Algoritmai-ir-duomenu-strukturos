package ADS4;

import java.util.ArrayList;
import java.util.List;

public class City
{
	private String name;
	private List<Flight> possibleFlights = new ArrayList<>();
	private int time = -1;
	private String minDistSetter = null;
	
	public City(String name)
	{
		this.name = name;
	}
	
	@Override
	public boolean equals(Object obj)
	{
		return obj instanceof City && name.equals(((City)obj).getName());
	}
	@Override
	public String toString()
	{
		return name;
	}
	
	public void linkWith(City otherCity, int depart, int arrive)
	{
		Flight flight = new Flight(this, otherCity, depart, arrive);
		if (!possibleFlights.contains(flight))
		{
			possibleFlights.add(flight);
		}
	}
	public void printLinks()
	{
		System.out.println("vvvvvvvvvvvvvvvv " + name + " vvvvvvvvvvvvvvvv");
		possibleFlights.forEach(flight -> System.out.println(flight));
		System.out.println("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
	}
	
	private void burn()
	{
		setTime(-1);
		setMinDistSetter(null);
	}
	public static void purge(List<City> heretics)
	{
		heretics.forEach(City::burn);
	}
	public static String fly(City from, City to)
	{
		from.setTime(0);
		from.expand(from, to);
		return to.getTime() == -1 || to.getMinDistSetter() == null
			   ? "No route found!"
			   : to.getMinDistSetter() +
						 " == " +
						 (to.getTime() / 60) +
						 ":" +
						 (to.getTime() % 60) +
						 " (" +
						 to.getTime() +
						 ")";
	}
	
	private void expand(City start, City finish, int prevArrival)
	{
		for (Flight flight : possibleFlights)
		{
			int maybeNewTime = getTime() + flight.getDurationWithWaitTime(prevArrival);
			City workingNode = flight.getEnd();		//workingNode ~ neighbour		//this ~ parent
			if ((workingNode.getTime() == -1 || workingNode.getTime() > maybeNewTime))
			{
				workingNode.setTime(maybeNewTime);
				flight.getEnd().setMinDistSetter(getMinDistSetter() + " -> " + flight.getEnd().getName());
				
				/*System.out.println(flight.getStart().getName() +
										   " setting " +
										   workingNode.getName() +
										   " to:: " +
										   getTime() +
										   "+" +
										   flight.getDurationWithWaitTime(prevArrival) +
										   "=" +
										   maybeNewTime);*/
				
				workingNode.expand(start, finish, flight.getArrival());
			}
			/*else
			{
				System.out.println(flight.getStart().getName() +
										   " NOT setting " +
										   workingNode.getName() +
										   " to:: " +
										   getTime() +
										   "+" +
										   flight.getDurationWithWaitTime(prevArrival) +
										   "=" +
										   maybeNewTime +
										   " > it is " +
										   workingNode.getTime());
			}*/
		}
		if (!equals(start) && !equals(finish))
		{
			setTime(-1);
		}
	}
	private void expand(City start, City finish)
	{
		for (Flight flight : possibleFlights)
		{
			flight.getEnd().setTime(flight.getDuration());
			flight.getEnd().setMinDistSetter(getName() + " -> " + flight.getEnd().getName());
			
			/*System.out.println(flight.getStart().getName() +
									   " setting " +
									   flight.getEnd().getName() +
									   " to: " +
									   flight.getDuration());*/
			
			flight.getEnd().expand(start, finish, flight.getArrival());
		}
	}
	
	public String getName()
	{
		return this.name;
	}
	
	public int getTime()
	{
		return this.time;
	}
	
	public String getMinDistSetter()
	{
		return this.minDistSetter;
	}
	
	public void setTime(int time)
	{
		this.time = time;
	}
	
	public void setMinDistSetter(String minDistSetter)
	{
		this.minDistSetter = minDistSetter;
	}
}
