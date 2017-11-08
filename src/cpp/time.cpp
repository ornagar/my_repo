#include <stdio.h>

class Time
{
	private:
		int hour;
		int min;
		int sec;
	public:
		Time(int h = 0, int m = 0, int s = 0);
		void print(void);
		Time operator+(Time b);
		bool operator==(Time b);
};

Time::Time(int h, int m, int s)
{
	hour = h;
	min = m;
	sec = s;
}

void Time::print(void)
{
	printf("%02d:%02d:%02d\n", hour, min, sec);
}

Time Time::operator+(Time b)
{
	Time temp;
	temp.sec = sec + b.sec;
	if (59 < temp.sec)
	{
		temp.min += temp.sec / 60;
		temp.sec %= 60;
	}
	temp.min += min + b.min;
	if (59 < temp.min)
	{
		temp.hour += temp.min / 60;
		temp.min %= 60;
	}
	temp.hour += hour + b.hour;
	if (23 < temp.hour)
	{
		temp.hour %= 24;
	}
	
	return (temp);
}


bool Time::operator==(Time b)
{
	return (hour == b.hour && min == b.min && sec == b.sec);
}

int main(void)
{
	Time a(2, 50, 20);
	Time b(2, 50, 20);
	Time c = a + b;

	c.print();
	
	printf("%d\n", a == b);
	
	return (0);
}
