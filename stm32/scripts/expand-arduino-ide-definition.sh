#!/bin/sh
#
# XXX Rewrite with python or something
#

RESULT="{$1}"; shift
FILES="$@"

# Enable the following line for debugging
# echo >&2 "Expanding $RESULT from $FILES"

# Expand as long as there are {variable} constructs in the result
while echo "$RESULT" | grep -q '{.*}'; do
    # Extract the variable name from the result
    VAR=`echo "$RESULT" | sed -e 's/.*{\([^}]*\)}.*/\1/'`
    # Find the first immediate expansion
    EXPANSION=`sed -n -e '/^#/d' -e "/$VAR=/{s/$VAR=[ \t]*//p
q}" $FILES | sed -e 's%/%\\\\/%g'`
    # echo "$VAR" "->" "$EXPANSION" >&2
    # Replace the variable with the expansion
    RESULT=`echo "$RESULT" | sed -e "s/{$VAR}/$EXPANSION/"`
done

echo $RESULT
