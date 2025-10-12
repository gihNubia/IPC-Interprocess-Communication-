#!/usr/bin/env bash
set -euo pipefail
export LC_ALL=C

runs=10
arg_val=100000
arg_step=100000
TIMEFORMAT='%R %U %S'

real_times=()
user_times=()
sys_times=()

for ((i=1; i<=runs; i++)); do
  timing=$({ time ./index "$arg_val" > /dev/null; } 2>&1)
  read -r real_s user_s sys_s <<< "$timing"

  real_times+=("$real_s")
  user_times+=("$user_s")
  sys_times+=("$sys_s")

  printf "Execução %2d | arg=%-7d | real=%-10s user=%-10s sys=%-10s\n" \
         "$i" "$arg_val" "$real_s" "$user_s" "$sys_s"

  arg_val=$((arg_val + arg_step))
done

avg_of_list() {
  awk '{s+=$1} END{if(NR>0) printf("%.6f", s/NR); else print "NaN"}'
}

avg_real=$(printf "%s\n" "${real_times[@]}" | avg_of_list)
avg_user=$(printf "%s\n" "${user_times[@]}" | avg_of_list)
avg_sys=$(printf "%s\n" "${sys_times[@]}" | avg_of_list)

echo
echo "Médias (em segundos) sobre $runs execuções:"
echo "real: $avg_real"
echo "user: $avg_user"
echo "sys : $avg_sys"