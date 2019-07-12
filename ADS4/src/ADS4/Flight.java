package ADS4;

public class Flight
{
	private City start, end;
	private int departure, arrival;
	
	public Flight(City startCity, City endCity, int departureTime, int arrivalTime)
	{
		start = startCity;
		end = endCity;
		departure = departureTime;
		arrival = arrivalTime;
	}
	
	@Override
	public String toString()
	{
		return "@" + departure + " " + start.getName() + " -> " + end.getName() + " @" + arrival + " = " + getDuration();
	}
	
	public int getDuration()
	{
		return arrival < departure ? 1440 + arrival - departure : arrival - departure;
	}
	
	public int getDurationWithWaitTime(int prevArrival)
	{
		//System.out.println(start.getName() + " - " + end.getName() + ": " + prevArrival + " " + getDuration() + " " + departure + " " + arrival);
		return getDuration() + (departure < prevArrival ? 1440 + departure - prevArrival : departure - prevArrival);
	}
	
	public City getStart()
	{
		return this.start;
	}
	
	public City getEnd()
	{
		return this.end;
	}
	
	public int getDeparture()
	{
		return this.departure;
	}
	
	public int getArrival()
	{
		return this.arrival;
	}
}
