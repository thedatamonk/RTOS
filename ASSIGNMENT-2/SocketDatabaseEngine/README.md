## Response times of the DatabaseEngine server to client requests under different situations.
The EchoEngine server receives a filename / filepath (as request) from the clients. If the file exists, then the server returns the contents of the file  else it returns `File doesn't exists`. Here response time is defined as the time difference between the moment **the client sent the request to the server** and the moment **the client received the response from the server**.
**(Note: Response times are in milliseconds)**

|   # of parallel clients     | Client_1 | Client_2 | Client_3 | Client_4 | Client_5 |
| --------------------------- |----------|----------|----------|----------|----------|
| 1                           | 0.0073   |          |          |          |          |
| 2                           | 0.0086   | 0.0076   |          |          |          | 
| 3                           | 0.0082   | 0.0096   | 0.0080   |          |          |
| 4                           | 0.0083   | 0.0104   | 0.0070   | 0.0096   |          |
| 5                           | 0.0094   | 0.0088   | 0.0085   | 0.0093   | 0.0097   |
