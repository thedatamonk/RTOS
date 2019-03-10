## Response times of the EchoEngine server to client requests under different situations.
The EchoEngine server receives a character (as request) from the clients and then reverses the case of the character. For instance, `A -> a` or `d -> D` etc. If the character is not an alphabet then it returns the same character. Here response time is defined as the time difference between the moment **the client sent the request to the server** and the moment **the client received the response from the server**.

**(Note: Response times are in milliseconds)**

|   # of parallel clients     | Client_1 | Client_2 | Client_3 | Client_4 | Client_5 |
| --------------------------- |----------|----------|----------|----------|----------|
| 1                           | 0.0081   |          |          |          |          |
| 2                           | 0.0086   | 0.0085   |          |          |          | 
| 3                           | 0.0092   | 0.0091   | 0.0092   |          |          |
| 4                           | 0.0094   | 0.0094   | 0.0094   | 0.0094   |          |
| 5                           | 0.0095   | 0.0095   | 0.0095   | 0.0095   | 0.0095   |
