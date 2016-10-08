readarray myarray < clarifaiauth.txt
readarray num < number.txt
readarray authkey < authkey.txt
python main.py ${myarray[0]} ${myarray[1]} ${num[0]} ${authkey[0]} ${authkey[1]}