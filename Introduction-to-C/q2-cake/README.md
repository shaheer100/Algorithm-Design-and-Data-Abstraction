a. Implement the function away_div(num, denom) which calculates the result of integer division (num/denom), rounding away from zero (as opposed to regular integer division, which rounds toward zero).
b. Implement the function num_cakes(gf, chocolate, vanilla, lemon, pieces_per_cake). This function calculates the minimum number of cakes needed for a party, given the total number of pieces of each type people want: gluten free (gf), chocolate, vanilla, and lemon. 

Each cake is sliced into pieces_per_cake pieces. You must order a whole number of each type of cake. For example, even if only one person wants a piece of chocolate cake, you have to order an entire cake. Of course, common sense dictates that the parameter values cannot be negative and you cannot have zero pieces_per_cake.
For example, the value of num_cakes(0, 1, 6, 4, 4) would be 4:

0 gluten free
1 chocolate
2 vanilla
1 lemon

c. Implement the function num_cakes_v2(gf, chocolate, vanilla, lemon, pieces_per_cake). This function calculates the minimum number of cakes needed for a party as in the previous question. This time, you are ordering from a shop that offers half-and-half cakes. For example, you can order a cake that is half chocolate, and half vanilla. 

However, to prevent cross-contamination, you cannot combine a gluten free cake with any other type. Note that you can still only order a whole number of cakes (that is, you cannot order half a cake by itself). So that there can be two equals halves, pieces_per_cake must be an even number.
For example, the value of num_cakes_v2(1, 2, 6, 2, 4) would be 4:

1 gluten free
1 chocolate / vanilla
1 vanilla
1 lemon
OR
1 gluten free
1 chocolate / lemon
2 vanilla
etc...
