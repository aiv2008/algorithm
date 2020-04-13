from sklearn.ensemble import RandomForestRegressor
import pandas as pd

def set_missing_ages(df): 
	age_df = df[['Age','Fare', 'Parch', 'SibSp', 'Pclass']]
	print(type(age_df))


if __name__ == "__main__":
	data_train = pd.read_csv("data/train.csv");
	set_missing_ages(data_train)
