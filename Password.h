#pragma once
//composed inside Person class
class Password
{
private:
	char* data;
	int length;
	int days_kept;
		int findlen() const;
		// helper fucntions for isvalid() check
		bool hasNumeric() const;
		bool hasUpper() const;
		bool hasSpecial()const;
		bool hasMinLength() const;
	

public:
	Password();
	Password(const char* data, int length);
	Password(const Password& other);
	Password& operator=(const Password& other);

	~Password();    
	bool isValid() const;
	//randomly generatign a strong password if user wishes when changing
	static Password generateStrong(bool userPermission);
	// if password not changed after 90+ days, at risk
	bool isAtRisk()const;

	//password change helpers
    bool matches(const char* input) const;  // verifies old password before allowing change
	void setPassword(const char* newData);         
	const char* get() const;  
	//file handling use             
	void incrementDays();                 // called whenver login ade to track days pass not changed

};
