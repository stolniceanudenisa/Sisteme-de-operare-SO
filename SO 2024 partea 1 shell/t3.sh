first=$1
_l="/etc/login.defs"
_p="/etc/passwd"

l=$(grep "^UID_MIN" $_l)
l1=$(grep "^UID_MAX" $_l)

echo "---Sysem User Accounts---"

users=$(awk -F':' '{print $1}' "$_p")
for user in $users
do
 if [ "$user" == "$first" ]
 then
 fi
done