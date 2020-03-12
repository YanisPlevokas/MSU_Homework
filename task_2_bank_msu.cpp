#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cstdlib> // для system
using namespace std;


string NotStated = "NOT STATED";

struct Payment
{
	string Currency;
	int Sum ;
	string ReceiverName ;
	string ReceiverNumber ;
};


void quickSortString(Payment* arr, int left, int right) 
{
	int i = left, j = right;
	Payment tmp;
	string pivot = arr[(left + right) / 2].ReceiverName;
	/* partition */
	while (i <= j) {
		while (arr[i].ReceiverName < pivot) 
		  {
		      i++;
		  }

		while (arr[j].ReceiverName > pivot) 
		      j--;
		if (i <= j) { 
		      tmp = arr[i];
		      arr[i] = arr[j];
		      arr[j] = tmp;
		      i++;
		      j--;
		}
	};

	/* recursion */
	if (left < j)
	quickSortString(arr, left, j);
	if (i < right)
	quickSortString(arr, i, right);
}

class Account
	{  
	public:
		static int EuroCourse;
		static int UsdCourse;
		static int CompletedTransactions;
		int PaymentsAmount;
		Payment* PaymentsHistory;
		string AccountNumber;
		string Currency;
		int Sum;

	public:
		Account()
		{
			PaymentsAmount = 0;
			PaymentsHistory = 0;
			Currency = "RUB";
			AccountNumber = NotStated;
			Sum = 0;
		}
		Account (const Account& copyAcc)
		{
			PaymentsAmount = copyAcc.PaymentsAmount;
			AccountNumber = copyAcc.AccountNumber;
			Currency = copyAcc.Currency;
			PaymentsHistory = (Payment*) realloc (PaymentsHistory, PaymentsAmount);
			for (int i = 0; i < PaymentsAmount; i++)
			{
				PaymentsHistory[PaymentsAmount - 1].Sum = copyAcc.PaymentsHistory[PaymentsAmount - 1].Sum;
				PaymentsHistory[PaymentsAmount - 1].Currency = copyAcc.PaymentsHistory[PaymentsAmount - 1].Currency;
				PaymentsHistory[PaymentsAmount - 1].ReceiverName = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverName;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumber = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNumber;
			}
		}

		~Account()
		{
			free(PaymentsHistory);
		}

		virtual const Account& operator=(const Account& NewAcc)
		{
			PaymentsAmount = NewAcc.PaymentsAmount;
			AccountNumber = NewAcc.AccountNumber;
			Currency = NewAcc.Currency;
			PaymentsHistory = NewAcc.PaymentsHistory;
			return *this;
		}





		void MakePayment(int SumOfPayment, string CurrencyOfPayment,  string ReceiverNameNew,  string ReceiverNumberNew)
		{
			if ((PaymentsAmount + 5) % 5 == 0)
			{
				PaymentsHistory = (Payment*) realloc (PaymentsHistory, PaymentsAmount);
			}
				CompletedTransactions++;
				PaymentsAmount++;
				PaymentsHistory[PaymentsAmount - 1].Sum = SumOfPayment;
				PaymentsHistory[PaymentsAmount - 1].Currency = CurrencyOfPayment;
				PaymentsHistory[PaymentsAmount - 1].ReceiverName = ReceiverNameNew;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumber = ReceiverNumberNew;
				Sum -= SumOfPayment;
		}

		void OutputLastPayment()
		{
			OutputPayment(PaymentsAmount);
		}
		void OutputPayment(int index) const
		{
			if (index > PaymentsAmount || index < 0)
				cout << "Out of Range" << endl;
			else
			{
				cout << PaymentsHistory[index].ReceiverName << " - Receiver Name" << endl;
				cout << PaymentsHistory[index].ReceiverNumber << " - Receiver Number" << endl;
				cout << PaymentsHistory[index].Currency << " - Currency" << endl;
				cout << PaymentsHistory[index].Sum << " - Sum of Payment" << endl;
				cout << "____________________" << endl;
			}
		}

		virtual void OutputInfo() = 0;

		int ComputeCosts() const
		{
			int localSum = 0;

			for (int i = 0; i < PaymentsAmount; i++)
			{
				if (PaymentsHistory[i].Currency == "EUR")
					localSum += PaymentsHistory[i].Sum * EuroCourse;
				if (PaymentsHistory[i].Currency == "USD")
					localSum += PaymentsHistory[i].Sum * UsdCourse;
				if (PaymentsHistory[i].Currency == "RUB")
					localSum += PaymentsHistory[i].Sum;
			}
			return localSum;
		}
		void OutputHistoryWithPerson(const string& Person, const string& Number) const
		{
			for (int i = 0; i < PaymentsAmount; i++)
			{
				if (PaymentsHistory[i].ReceiverName == Person && PaymentsHistory[i].ReceiverNumber == Number)
					OutputPayment(i);
			}	
		}
		void OutputHistory() const
		{
			for (int i = 0; i < PaymentsAmount; i++)
			{
				OutputPayment(i);
			}
		}
		void SortByReceiverNames()
		{
			quickSortString(PaymentsHistory, 0, PaymentsAmount - 1);
		}


	};
	int Account::EuroCourse = 77;
	int Account::UsdCourse = 68;
	int Account::CompletedTransactions = 0;


class LawAccount : public Account
	{	
		string NumberOfLawFirm;
		string NameOfLawFirm;
	public:
		LawAccount()
		{
			PaymentsAmount = 0;
			PaymentsHistory = 0;
			Currency = "RUB";
			AccountNumber = NotStated;
			Sum = 0;
			NumberOfLawFirm = NotStated;
			NameOfLawFirm = NotStated;
		}

		LawAccount (const LawAccount& copyAcc)
		{
			PaymentsAmount = copyAcc.PaymentsAmount;
			AccountNumber = copyAcc.AccountNumber;
			Currency = copyAcc.Currency;
			NumberOfLawFirm = copyAcc.NumberOfLawFirm;
			NameOfLawFirm = copyAcc.NameOfLawFirm;
			PaymentsHistory = (Payment*) realloc (PaymentsHistory, PaymentsAmount);
			for (int i = 0; i < PaymentsAmount; i++)
			{
				PaymentsHistory[PaymentsAmount - 1].Sum = copyAcc.PaymentsHistory[PaymentsAmount - 1].Sum;
				PaymentsHistory[PaymentsAmount - 1].Currency = copyAcc.PaymentsHistory[PaymentsAmount - 1].Currency;
				PaymentsHistory[PaymentsAmount - 1].ReceiverName = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverName;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumber = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNumber;
			}
		}

		virtual const LawAccount& operator=(const LawAccount& NewAcc)
		{
			PaymentsAmount = NewAcc.PaymentsAmount;
			AccountNumber = NewAcc.AccountNumber;
			Currency = NewAcc.Currency;
			for (int i = 0; i < PaymentsAmount; i++)
			{
				PaymentsHistory[PaymentsAmount - 1].Sum = NewAcc.PaymentsHistory[PaymentsAmount - 1].Sum;
				PaymentsHistory[PaymentsAmount - 1].Currency = NewAcc.PaymentsHistory[PaymentsAmount - 1].Currency;
				PaymentsHistory[PaymentsAmount - 1].ReceiverName = NewAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverName;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumber = NewAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNumber;
			}
			NumberOfLawFirm = NewAcc.NumberOfLawFirm;
			NameOfLawFirm = NewAcc.NameOfLawFirm;
			return *this;
		}
		void changeInfo(string CurrencyNew = "RUB" , string AccountNumberNew = NotStated, int SumNew = 0, string NumberOfLawFirmNew = NotStated, string NameOfLawFirmNew = NotStated)
		{
			Currency = CurrencyNew;
			AccountNumber = AccountNumberNew;
			Sum = SumNew;
			NumberOfLawFirm = NumberOfLawFirmNew;
			NameOfLawFirm = NameOfLawFirmNew;

		}
		virtual void OutputInfo()
		{
			cout << NumberOfLawFirm << " - number of law firm" << endl;
			cout << NameOfLawFirm  << " - name of law firm" << endl;
			cout << Sum << " - current sum" << endl;
			cout << AccountNumber << " - account number" << endl;
			cout << PaymentsAmount << " - payments amount" << endl;
		}
		const Payment& operator[](int index)
		{
			if (index < PaymentsAmount)
				return PaymentsHistory[index];
			else
			{
				cout << "Mistake" << endl;
				Payment a;
				return a;
			}

		}
		friend std::ostream& operator<< (std::ostream &out, const LawAccount &point)
		{
			out << point.NumberOfLawFirm << " - number of law firm" << endl;
			out << point.NameOfLawFirm  << " - name of law firm" << endl;
			out << point.Sum << " - current sum" << endl;
			out << point.AccountNumber << " - account number" << endl;
			out << point.PaymentsAmount << " - payments amount" << endl;
			return out;
		}
	};


class UserAccount : public Account
	{	
		string NumberOfUserIDN;
	public:
		UserAccount()
		{
			PaymentsAmount = 0;
			PaymentsHistory = 0;
			Currency = "RUB";
			AccountNumber = NotStated;
			Sum = 0;
			NumberOfUserIDN = NotStated;
		}
		UserAccount (const UserAccount& copyAcc) 
		{
			PaymentsAmount = copyAcc.PaymentsAmount;
			AccountNumber = copyAcc.AccountNumber;
			Currency = copyAcc.Currency;
			NumberOfUserIDN = copyAcc.NumberOfUserIDN;
			PaymentsHistory = (Payment*) realloc (PaymentsHistory, PaymentsAmount);
			for (int i = 0; i < PaymentsAmount; i++)
			{
				PaymentsHistory[PaymentsAmount - 1].Sum = copyAcc.PaymentsHistory[PaymentsAmount - 1].Sum;
				PaymentsHistory[PaymentsAmount - 1].Currency = copyAcc.PaymentsHistory[PaymentsAmount - 1].Currency;
				PaymentsHistory[PaymentsAmount - 1].ReceiverName = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverName;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumber = copyAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNumber;
			}
		}
		void changeInfo(string CurrencyNew = "RUB" , string AccountNumberNew = NotStated, int SumNew = 0, string NumberOfUserIDNNew = NotStated)
		{
			Currency = CurrencyNew;
			AccountNumber = AccountNumberNew;
			Sum = SumNew;
			NumberOfUserIDN = NumberOfUserIDNNew;
		}
		virtual const UserAccount& operator=(const UserAccount& NewAcc) 
		{
			PaymentsAmount = NewAcc.PaymentsAmount;
			AccountNumber = NewAcc.AccountNumber;
			Currency = NewAcc.Currency;
			PaymentsHistory = (Payment*) realloc (PaymentsHistory, PaymentsAmount);
			for (int i = 0; i < PaymentsAmount; i++)
			{
				PaymentsHistory[PaymentsAmount - 1].Sum = NewAcc.PaymentsHistory[PaymentsAmount - 1].Sum;
				PaymentsHistory[PaymentsAmount - 1].Currency = NewAcc.PaymentsHistory[PaymentsAmount - 1].Currency;
				PaymentsHistory[PaymentsAmount - 1].ReceiverName = NewAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverName;
				PaymentsHistory[PaymentsAmount - 1].ReceiverNumber = NewAcc.PaymentsHistory[PaymentsAmount - 1].ReceiverNumber;
			}
			NumberOfUserIDN = NewAcc.NumberOfUserIDN;
			return *this;
		}

		virtual void OutputInfo()
		{
			cout << NumberOfUserIDN << " - number of user IDN" << endl;
			cout << Sum << " - current sum" << endl;
			cout << AccountNumber << " - account number" << endl;
			cout << PaymentsAmount << " - payments amount" << endl;
		}
		friend std::ostream& operator<< (std::ostream &out, const UserAccount &point)
		{
			out << point.NumberOfUserIDN << " - number of user IDN" << endl;
			out << point.Sum << " - current sum" << endl;
			out << point.AccountNumber << " - account number" << endl;
			out << point.PaymentsAmount << " - payments amount" << endl;
			return out;
		}
		const Payment& operator[](int index)
		{
			if (index < PaymentsAmount)
				return PaymentsHistory[index];
			else
			{
				cout << "Mistake" << endl;
				Payment a;
				return a;
			}

		}


	};



int main ()
{
	LawAccount Yanis;
	UserAccount Ivan, Andrey;
	Ivan.changeInfo("123", "asd", 1234, "FASF");
	Yanis.MakePayment(123, "RUB", "Dmitriy", "24331");
	Yanis.OutputHistory();
	cout << Yanis << endl;
	Payment rock = Yanis[0];
	
  return 0;
}
