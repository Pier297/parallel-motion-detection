we can hide the costs of creating the threads by doing in parallel the processing of the first background frame.

in the parallel implementation it might be better to re-use the memory of Mat given that access to the heap is sequential.