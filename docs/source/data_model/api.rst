.. OmniSciDB Data Model

==================================
External API
==================================

OmniSciDB uses Apache's Thrift software framework for all external client communication.  The open source clients shipped with the repository include OmniSci's `heavysql` command line process, JDBC driver and SQLImporter utility.  For a full list of Thrift enabled clients supported by OmniSci see Table :ref:`omnisci-open-source-clients` below. The full list of thrift API methods can be found in the `heavy.thrift` file in the root of the OmniSciDB source directory.

All internal communication between the discrete processes within OmniSciDB also use the Thrift communication framework.  For example, communications between OmniSciDB and Apache Calcite are facilitated via Thrift.


#######
Design
#######

OmniSci has developed a rich set of Thrift based API calls.  The bindings for the these calls can be found in the file `heavy.thrift` in the open source repository.

The classes generated from the Thrift bindings include `HeavyProcessor`, `HeavyClient` and `HeavyIf`. The OmniSci code sitting 'behind' these classes can be found in the class `DBHandler`, in the file `ThriftHandler/DBhandler.(cpp/h)`.

The class OmniSci class `DBHandler` implements the generated interface `HeavyIf`.  The OmniSci server (in `MapDServer.cpp`) create an instance of `DBHandler`, using this object to initialize two instances of `apache::ThreadedServer` objects - one per Thrift protocol supported by the server (see section below for protocol details).

OmniSci clients such as the JDBC driver use the generated HeavyClient class to make calls through to the server.  To maintain state across client calls to the  Thrift bindings, an initial connection/validation process returns a session identifier as a `TSessionId` to the connecting client; subsequent calls need to include the session identifier as part of the serialised data structure.

In the case of Thrift communication with the `Calcite` server, Calcite acts as the communication server and the database acts as the client.  The `Calcite` Thrift bindings can be found in `java/thrift/calciteserver.thrift` in the repository. The `DBHandler` class (called from `MapdServer.cpp`) creates an instance of the Calcite class, a class generated by Thrift from the `calciteserver.thrift` binding which implements the client portion of the framework.  The Java Calcite server creates an apache::TThreadPoolServer to handle API calls.  The OmniSci code written to process the API calls can be found in the file `CalciteServerHandler.java` under `java/calcite` in the repository.


##########
Protocols
##########

The OmniSci database server presents the Thrift interface using either Thrift's 'binary' or 'json' protocols. When using json, Thrift will wrap the payload in a either a http or https header.  For simplicity, in this document reference to http and https will be used to mean  http/json and https/json.

The Thrift framework offers support for SSL/TLS encryption of links between clients and servers.  OmniSci uses this feature to secure/encrypted communications between both its external clients and the main server and its internal process.  The database system can process binary encrypted connections and https connections.  To manage https communications, OmniSci provides a web_server to act as a proxy to the normal http port opened by the server.  Table :ref:`omnisci-open-source-clients` below lists the protocols supported by each of the clients.

As mentioned in the 'Design' section the server opens two ports, a binary port and a http port - whether or not these ports and encrypted and which specific ports number are used is configurable at startup; either through command line parameters or a configuration files. The server can not open a port for a specific protocol in both both encrypted and non-encrypted format; for example it can not open a `binary` port and `binary encrypted` port.

.. table:: OmniSci Open Source Clients
   :name: omnisci-open-source-clients

   ============== ===================================
   Client process Protocols
   ============== ===================================
   JDBC Driver     Binary/Binary Encrypted/HTTP/HTTPS
   heavysql        Binary/Binary Encrypted/HTTP/HTTPS
   SQLImporter     Binary/HTTP/HTTPS
   KafkaImporter   Binary/HTTP/HTTPS
   StreamInserter  Binary/HTTP/HTTPS
   Pymapd          Binary/Binary Encrypted/HTTP/HTTPS
   Julia           Binary
   ============== ===================================
