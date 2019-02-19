## Response times of the DatabaseEngine server to client requests under different situations.
The EchoEngine server receives a filename / filepath (as request) from the clients. If the file exists, then the server returns the contents of the file  else it returns `File doesn't exists`. Here response time is defined as the time difference between the moment **the client sent the request to the server** and the moment **the client received the response from the server**.
### 1 client is running
|   Clients     | Reponse time (ms)  |
| ------------- | ------------------:|
| Client_1      | 0.00475            |

### 2 clients are running simultaneously
|   Clients     | Reponse time (ms)  |
| ------------- | ------------------:|
| Client_1      | 0.00516            |
| Client_2      | 0.00517            |

### 3 clients are running simultaneously
|   Clients     | Reponse time (ms) |
| ------------- | -----------------:|
| Client_1      | 0.00557           |
| Client_2      | 0.00517           |
| Client_3      | 0.00856          |

### 4 clients are running simultaneously
|   Clients     | Reponse time (ms) |
| ------------- | -----------------:|
| Client_1      | 0.00596           |
| Client_2      | 0.00584           |
| Client_3      | 0.00559           |
| Client_4      | 0.00543           |

### 5 clients are running simultaneously
|   Clients     | Reponse time (ms) |
| ------------- | -----------------:|
| Client_1      | 0.00573           |
| Client_2      | 0.00572           |
| Client_3      | 0.00522           |
| Client_4      | 0.00530           |
| Client_5      | 0.00515           |

