# Low-Latency Financial Event Router - System v0 ##

## 1. Problem:
There is a lot of news that hits people's inbox daily, and even more are the news providers. For a trader/investor to position themselves
they need to read the news, and most of which wastes their time, because there is nothing going on in the market. If they wanna apply the "Eat the Frog" principle, they need a system that can tell them what all is important, and what is noise. And the system MUST be low latency, because market, as we all know it, waits for no one, and rewards the fastest. Therefore this system exists.

## 2. Input:
The data from the news sources, and gets classified right when the news hits the source. the news event may contain source, timestamp, headline/text, maybe id.
using *** FinnHub *** for  news data for v0, it receives:  
category: News category.
datetime: Published time in UNIX timestamp.
headline: News headline.
id: News ID. This value can be used for minId params to get the latest news only.
related: Related stocks and companies mentioned in the article.
source: News source.
summary: News summary.
url: URL of the original article.


## 3. Output
the classified/sorted news will be saved in jsonl/csv file, and later we'll bring the system to have a database, along with live C++ cli. the output will be classification, along with a confidence score, and a rating out of 5. and overall low latency

## 4. Routing Categories
there are 4 categories, 1. URGENT: causes a comperatievely significant change in stock market. something worth checking becuase it dones't happen usually, 2. IMPORTANT: Causes a big change but not that big, 3. MONITOR: something big that will be replaced by another news and 4. IGNORE: useless to stock market, almost no change will be created, and even if it does it wont be lasting for long. 
IGNORE = no meaningful market relevance, and if there is it must have very less to no impact on market
MONITOR = potentially relevant, but no immediate attention needed, and less impact on the market
IMPORTANT = clearly market-relevant and deserves attention, creates a bigger impact on the market
URGENT = time-sensitive, high-impact event requiring immediate attention, serious impact on the market

## 5. System Responsibilities
receive an event, parse the input, safely hand it off to the decision model along with everything in its api requirements, receive the output, and parse it, place the output in that perticular section of the csv file along with teh score and everything (file update). measuring the latencies and saving them in the file too. 

## 6. Non-Responsibilities
the news sender portal, and their websocket tick (or whatever that is), managing/handeling cloudflare and the way the decisons are being made. no technical advice is being given, and no stock prices are being predicted. how the news router will be used and in what field.

## 7. Non-Functional Requirements
make sure the system has low latency, not providing corrupt data to the file/db, all the information that is coming form decision model is accurately being presented to the user with a layer of abstraction. the system should feel simple to use when on github. secrets must not leak, decision engine must be replacable, failures and latency must be observable. 


## 8. Event Record
event
- id: well because it is ID
- source: to keep notes of where the news are coming from
- timestamp: to be able to tell when the news is from
- headline: the most Important part to make a decision
- body: what's inside the news
- route: where is the news placed by the decision model
- confidence: the score assigned by decision model that tells the amount of belif it has in the success of it
- decision_engine: to test the latency
- decision_latency_ms: to test the latency of that particular decision model
- total_latency_ms: to keep the system in check and make sure the latency is low
- status: what happened to the news