package ADS4;

import java.util.ArrayList;

public class FindableList<T> extends ArrayList<T>
{
	public FindableList(){}
	
	public T find(T other)
	{
		for (T thing : this)
		{
			if (thing.equals(other))
			{
				return thing;
			}
		}
		return null;
	}
}
