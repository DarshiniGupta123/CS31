#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value)
{
	if (n < 0) // if the number of elements the user inputs is negative 
		return -1;
	else
	{
		for (int i = 0; i < n; i++)
			a[i] += value; // adds the value to each element in the array
		return n; //returns the number of elements
	}
}

int lookup(const string a[], int n, string target)
{
	int answer = -1;
	if (n < 0)
		answer = -1;
	else 
	{
		for (int i = 0; i < n; i++) //loops through array
		{
			if (a[i] == target) //if the element equals the target
			{
				answer = i; //the index is put in answer and then breaks out of the for loop to not get the next index value where the element equals the target
				break;
			}
		}
	}
	return answer;
}

int positionOfMax(const string a[], int n)
{
	string max = a[0]; //sets the max to the first element for comparison
	int index = 0;
	if (n < 0)
		index = -1;
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (a[i] >= max) //if the next element if bigger than the max, then  the max equals the this element and index is set to that certain counter
			{
				max = a[i];
				index = i;
			}
		}
	}
	return index;
}

int rotateLeft(string a[], int n, int pos)
{
	int position = -1;
	if (n < 0 || pos < 0 || pos > n)//if the position to be moved is less than 0 and greater than n
	{
		position = -1;
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (i == pos) //if the index equals the position
			{
				string temp = a[i];//set a temp variable to the element because the element at index i will be replaced with i + 1
				while (i < (n - 1))
				{
					a[i] = a[i + 1];// moves each element string one place to the left
					i++;
				}
				a[n-1] = temp;//the position string is moved to the element at the end
				position = 1;
				break; //so the for loop doesn't continue after the index equals the position
			}
		}
	}
	return position;
}

int countRuns(const string a[], int n)
{
	int answer = -1;
	int num = 1; //because there is at least one element in an array if the array is not empty
	if (n < 0)
		answer = -1;
	else if (n == 0) //if there are 0 elements than there will be a 0 number of sequences
		answer = 0;
	else 
	{
		for (int i = 0; i < (n - 1); i++)
		{
			if (a[i] == a[i + 1]) // if the two elements right next to each other are equal 
				num += 0; //the number does not add anything
			else
				num++; //the number of sequences add one if the two elements are not the same
		}
		answer = num;
	}
	return answer; //returns the number of sequences
}

int flip(string a[], int n)
{
	int solution = -1;
	if (n < 0)
		solution = -1;
	else
	{
		int j = n - 1; // variable for the last element index
		int i = 0; // variable for the first element index
		while (i < j) 
		{
			string temp = a[j]; //beacuse after the next command the value in a[j] will become a[i] and so you would not be able to store a[j] into a[i]
			a[j] = a[i]; //the last element equals the first element
			a[i] = temp;
			j--; //the last element index decrements
			i++; //the first element index increments
		}
		solution = n;
	}
	return solution; //returns the number of elements
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	int index = 0;
	int num = 0;
	if ((n1 < 0) || (n2 < 0)) //if both number of elements are less than 0
		return index = -1;
	else
	{
		int size = 0;
		if (n1 < n2) // gets the smallest size between the two array lengths
			size = n1;
		else
			size = n2;
		int i = 0;
		while ((a1[i] == a2[i]) && (i < size)) //while the two arrays equal each other and its less than the size of the smallest array
		{
			num++; //increments the index
			i++;
		}
		index = num;
	}
	return index; //returns when the two arrays do not equal each other 
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	int index = -1;
	int num = 0;
	if ((n1 < 0) || (n2 < 0))
		return index = -1;
	else if (n2 == 0) // if the length of the subsequence is 0 the the index is 0
		index = 0;
	else
	{
		int temp = 0;
		int i = 0;
		for (int j = 0; j < n1; j++)
		{
			if (a1[j] == a2[i]) // if the elements equal each other
			{
				temp = j; //sets the index to a temp variable if the subsequence equals in the other sequence
				while ((a1[j] == a2[i]) && (i < n2))
				{
					i++;
					j++;
					num++; //adds the number of equal elements in a row
				}

			}
			if (num == n2) //if the number of equals elements in a row equals the subsequence
			{
				index = temp; 
				break;
			}
		}
	}
	return index; //returns where the subsequence starts in the first array
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	int position = -1;
	int max = 0;
	if (n1 < 0 || n2 < 0)
		position = -1;
	else
	{
		for (int i = 0; i < n2; i++) //loops through both arrays
		{
			for (int j = 0; j < n1; j++)
			{
				if (a2[i] == a1[j]) //if the two elements equal each other
				{
					position = j; // position equals the lower index and breaks so that is does not check for later equal elements
					break;
					
				}
			}
		}
			
	}
	return position;//returns the first index where the two elements in the two arrays are equal

}

int split(string a[], int n, string splitter)
{
	int index = 0;
	string temp = "";
	if (n < 0)
		index = -1;
	else
	{
		for (int j = n - 1; j >= 0; j--)// the element counter starts at the end of array
		{
			for (int i = 0; i < j; i++)// this element counter starts at the beginning of the array
			{
				if (a[j] < splitter) //when the array element is less than the splitter
				{
					temp = a[i]; //the element less than the splitter is put in the beginning of the array and the other element at the index j until the element in index j is greater than the splitter
					a[i] = a[j];
					a[j] = temp;
				}
		
			}
		}
		for (int c = 0; c < n; c++)
		{
			if (a[c] >= splitter) //finds the first index where the element is greater than the splitter
			{
				index = c;
				break;
			}
			else
				index = n;
		}
	}
	return index;
}


int main()
{
	string h[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
	assert(lookup(h, 7, "logan") == 5);
	assert(lookup(h, 7, "diana") == 2);
	assert(lookup(h, 2, "diana") == -1);

	string r[3] = { "selina", "reed", "selina" };
	assert(lookup(r, 3, "selina") == 0);

	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "selina", "reed", "peter", "sue" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "selina?" && g[3] == "sue?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "peter?" && g[3] == "reed?");

	string e[4] = { "diana", "tony", "", "logan" };
	assert(subsequence(h, 7, e, 4) == 2);
	assert(subsequence(r, 3, g, 4) == -1);
	assert(subsequence(g, 4, r, 3) == -1);

	string d[5] = { "reed", "reed", "reed", "tony", "tony" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "peter", "diana", "steve" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(lookupAny(f, 3, h, 7) == 0);
	assert(flip(f, 3) == 3 && f[0] == "steve" && f[2] == "peter");

	assert(split(h, 7, "peter") == 3);
	assert(split(g, 4, "reem") == 2);
	assert(split(g, 0, "peter") == 0);
	assert(split(g, 4, "zed") == 4);

	cout << "All tests succeeded" << endl;
}