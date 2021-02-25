### Sorting Elements of Matrices

Sorting every element of a (square) matrix is almost exactly the same as sorting a one-dimensional structure of `size`
squared. You cannot do two sorts, on each row then the main pointer array, because the all the elements will not be
sorted in relation to each other. (This does, however, seem to make a matrix the perfect candidate for some type of
Merge Sort.)

The major detail that comes up in sorting a matrix is transferring between rows. For example, one of the major Bubble
Sort methods is to iterate from index `1` to index `length - 1`, swapping `i` and `i-1`, which is impossible in a nested
Structure, due to bound overflows. The problem cannot be remedied by simply iterating from `1` to `size^2 -1`, using
position `i/size, i%size` for two reasons. First, extra logic is still required to return to the previous subarray
when `i%size == 0`.
(This can be done either by calculating the last position every time, or having a `last` variable and doing the subarray
transfer logic on
`i` increment.) Second, Each array has a four byte overhead, requiring more extra logic, such as size (iterating `i`
through `size^2 + arr::length -1`), and skipping 4 bytes every subarray transition (which is annoying to implement even
if it's an integer structure and you can simply skip one element every time).

##### <u>Bubble Sort</u>

Bubble Sorting a matrix is almost as simple as to an array. Until the array is sorted (max `size^2 -1` times), Iterate
through every element, swapping the current element for the last element if the last element is larger, then setting the
last element to the current element.

##### <u>Insertion Sort</u>

Insertion sorting a matrix requires a large leap in logic from doing the same for an array. In Bubble Sort, each
iteration we need to calculate `currentPosition -1` once; in insertion sort, we decrement
(potentially) throughout the entire structure, requiring each time a decrement of the `([row][column]) column` index,
and then logic for subarray transfers, as well as the re-increment of the same decremented index to ensure it's smaller
to continue decrementing.

##### <u>Selection Sort</u>

As the "opposite" of Insertion Sort, Selection Sort is almost exactly a two dimensional version of the code for the
normal Selection Sort. Iterating though `row` and `column` (as opposed to just size), iterate through every
remaining `row` and `column` (as opposed to size), until you find the smallest element, then switch with the current
one.