## Overview

QuaLLA is primarily a shared library designed to be used by C++, Python and C applications,
but it does come with a suite of user-friendly tools for demos, experiments, testing and validation.

The following tools are included in the default packages:

- `qualla-dialog`     -- LLM queries via qualla::Dialog API
- `qualla-perplexity` -- Perplexity measurement tool
- `qualla-instruct`   -- LLM requests & responses via JSON Lines interface (supports Dolly datasets)
- `qualla-embedd`     -- Sentence Transformer queries via qualla::Embedding API

All tools come with shell wrapper scrips (`qualla-dialog.sh`, etc) that properly setup the required 
environment variables (such as `LD_LIBRARY_PATH` and `ADSP_LIBRARY_PATH`). For the common use-cases 
it usually makes sense to use the wrapper scripts.

## Configuration files

All QuaLLA tools require JSON configuration file that configures various components such as Tokenizer,
LLM Engine, Model, and Sampler.

See [LLaMa-7B-Chat based assistant configuration file](../conf/dialog/assistant.json) for an example.

Default qualla source and binary packages include configuration files for various target devices.
The are installed under `conf/dialog` and `conf/embedding` folders.

## Basic usage on an Android device (e.g Lanai)

```
$ adb shell
# cd /data/local/tmp/qualla-latest ### or wherever you installed the binary package
# ./bin/qualla-dialog.sh --conf conf/dialog/lanai.qnn-htp.llama-7b.json --ask 'what is the most popular cookie in the world?'
...
```

## Basic usage on a Windows device (e.g. Hamoa)

```
$ ssh -t hcktest@192.168.1.210 'c:\git\bin\sh'
$ cd qualla-latest/   ### or wherever you installed the binary package
$ ./bin/qualla-dialog.sh --conf conf/dialog/ggml.llama-13b.json --prime 'You are the Darth Vader!' --ask 'How are you feeling?'
```
## Using qualla-dialog

`qualla-dialog` tool exposes most of the `qualla::Dialog` API features:

- Ask/Query with complete or partial sentences
- Priming (aka providing Context) to the model
- Save/Restore/Reset of the dialog history
- Measuring KPIs such as Tokens-per-Second
- See `qualla-dialog.sh --help` for mode details 

Here are some example of how to use `qualla-dialog` tool:

### Simple queries (question/answer)

```
# ./bin/qualla-dialog.sh --conf conf/dialog/lanai.qnn-htp.llama-7b.json --ask 'what is the most popular cookie in the world?'
...
QUALLA:INFO Model dir   : ./models/llama-v2/7B-FT
...
Q: what is the most popular cookie in the world?
A: The most popular cookie in the world is the Chocolate Chip Cookie. It is a classic cookie that consists of chunks of chocolate
 embedded in a sweet, chewy dough. It is a favorite among both children and adults and is enjoyed in many countries around the world.
```

### Save/Restore and Reset

```
$ ./bin/qualla-dialog.sh --conf conf/dialog/lanai.qnn-htp.llama-7b.json --prime 'You are Darth Vader!' --save vader 
...
P: You are Darth Vader!
QUALLA:INFO dialog-save: saving as vader ./cache/vader

$ ./bin/qualla-dialog.sh --conf conf/dialog/lanai.qnn-htp.llama-7b.json \
     --restore vader --ask 'How are you feeling?' \
     --reset --ask 'And how are you feeling now?'
...
QUALLA:INFO dialog-restore: restoring from vader ./cache/vader
Q: How are you feeling?
A:  Impatience. The Force is strong with me... *growls*

QUALLA:INFO dialog-reset: sample
Q: And how are you feeling now?
A:  I'm feeling well, thank you for asking! The sun is shining brightly and I'm ready to tackle any task that comes my way. How about you?
```

### Document summary and showing KPIs

```
./bin/qualla-dialog.sh --conf conf/dialog/lanai.qnn-htp.llama-7b.json --show-kpis --prime - \
     --ask 'Please summarize previous passage.' < ../hawaii
...
P: Hawaii island state in the Western United States, about 2,000 miles (3,200 km) from the U.S. mainland ...
...
KPI: Prompt 1769.02 (msec) 527.43 (t/s)
...
Q: Please summarize previous passage.
A:  The passage describes the state of Hawaii in the United States. It highlights the unique features of the state, ... 

KPI: Prompt 1368.73 (msec) 10.96 (t/s)
KPI: Generate 6951.44 (msec) 11.22 (t/s)
```

## Using qualla-perplexity

`qualla-perplexity` tool computes Perplexity Scores for a given dataset.
Typical dataset used for this is [WikiText-2](https://s3.amazonaws.com/research.metamind.io/wikitext/wikitext-2-raw-v1.zip?ref=blog.salesforceairesearch.com)

Here is an example of how to use `qualla-perplexity` tool:

```
# ./bin/qualla-perplexity.sh --conf conf/dialog/lanai.ggml.llama-7b.json --dataset wiki.test.raw.small
Qualla Version: 0.9.7
QUALLA:INFO ggml: loading model ./models/llama-v2/7B-FT/ggml-model-q4_4.gguf
loading dataset ...
dataset: text-size 32379
tokenizing dataset (takes awhile) ...
dataset: tokens-size 8299
perplexity: 8299 tokens 8 chunks
[1]5.0257 (57661.45 msec)
...
```

## Using qualla-instruct

`qualla-instruct` tool is similar to `qualla-dialog` but uses a different interface/protocol.
It expects JSON Lines as the input, and provides JSON Lines as the output.

The tool supports two modes: `--mode api` and `--mode dolly`.
The API mode simply exposes most `qualla::Dialog` API methods via JSON Lines, where as the Dolly mode expects 
Dolly-15K JSON Lines format on the input.

*Also note that in the Dolly mode the state of the model/dialog is reset for each context/instruction.*

See examples below for details.

### API mode 

```
# ./bin/qualla-instruct.sh --conf conf/dialog/lanai.qnn-htp.llama-7b.json --mode api                                                
>{"kpi":null,"response":"ready","status":"OK"}
<{"op": "ask", "param": "How far is Jupiter from the sun?"}
>{"kpi":{"generate-msec":2494.524,"generate-tps":11.625473976135254,"prompt-msec":1753.349,"prompt-tps":23.3841552734375},"response":"  Jupiter is approximately 778.3 million kilometers (483.8 million miles) away from the Sun.","status":"OK"}
```
*Note that `>` for output and `<` for input, in this example are for illustrational purposes only (i.e not present in the actual usage)*

Supported operations (i.e API methods)

- `{"op": "query-begin",    "param": "begining of sentence"}`
- `{"op": "query-continue", "param": "continuation of sentence"}`
- `{"op": "query-end",      "param": "end of sentence"}`
- `{"op": "ask",     "param": "complete sentence"}`
- `{"op": "save",    "param": "session name"}`
- `{"op": "restore", "param": "session name"}`
- `{"op": "reset"}`

*partial sentences are handled differently depending on how the instruction and prompt tags are configured in the dialog/assistant.json*

### Dolly mode

```
./bin/qualla-instruct.sh --conf conf/dialog/lanai.qnn-htp.llama-7b.json --mode dolly
>{"kpi":null,"response":"ready","status":"OK"}
<{"instruction": "What is the average lifespan of a Golden Retriever?", "context": "Golden Retrievers are a generally healthy breed; they have an average lifespan of 12 to 13 years. Irresponsible breeding to meet high demand has led to the prevalence of inherited health problems in some breed lines, including allergic skin conditions, eye problems and sometimes snappiness. These problems are rarely encountered in dogs bred from responsible breeders.", "response": "The average lifespan of a Golden Retriever is 12 to 13 years."}
>{"kpi":{"generate-msec":4346.956,"generate-tps":11.732407569885254,"prompt-msec":1911.434,"prompt-tps":11.50973129272461},"response":"  The average lifespan of a Golden Retriever is 12 to 13 years. However, with proper care and attention to health issues, some Golden Retrievers have been known to live up to 15 years or more.","status":"OK"}
```

*Note that `>` for output and `<` for input, in this example are for illustrational purposes only (i.e not present in the actual usage)*

Another way to use this tool is to directly feed the dolly dataset on the input.

```
$ export QD=/data/local/tmp/qualla-latest
$ adb shell $QD/bin/qualla-instruct.sh --conf $QD/conf/dialog/lanai.qnn-htp.llama-7b.json --basedir $QD --log-output $QD/instruct.log.txt \
      --mode dolly < databricks-dolly-15k.jsonl
{"kpi":null,"response":"ready","status":"OK"}
{"kpi":{"generate-msec":3331.832,"generate-tps":11.705352783203125,"prompt-msec":1388.843,"prompt-tps":11.520471572875977},"response":"  Virgin Australia, the trading name of Virgin Australia Airlines Pty Ltd, started operating on August 31, 2000, with two aircraft on a single route.","status":"OK"}
{"kpi":{"generate-msec":1142.028,"generate-tps":12.258957862854004,"prompt-msec":1761.614,"prompt-tps":25.545394897460938},"response":"  Tope is a species of fish, not rope.","status":"OK"}
{"kpi":{"generate-msec":6835.293000000001,"generate-tps":11.411486625671387,"prompt-msec":1776.395,"prompt-tps":24.206626892089844},"response":"  Camels can survive for long without water due to their ability to conserve water through various adaptations, such as storing water in their fat reserves and limiting their water loss through their highly efficient kidneys. They can also go without water for extended periods by relying on their diet of foods with high water content, such as plants and fruits.","status":"OK"}
{"kpi":{"generate-msec":978.9350000000001,"generate-tps":12.258357048034668,"prompt-msec":1770.675,"prompt-tps":32.19160461425781},"response":"  The third daughter's name is Emily.","status":"OK"}
```
## Using qualla-embedd

`qualla-embedd` tool provides a simple text-to-embedding interface based on `qualla::Embedding` API.

Here is an example:

```
./bin/qualla-embedd.sh --conf conf/embedding/minilm.ggml.json --query "Hello!"
QUALLA:INFO bert: loading model /data/local/tmp/qualla-latest/models/minilm-v2/ggml-model-f16.bin
...
Q: Hello!
E: [-0.08214737, 0.016507221, 0.022135092, -0.0070867646, ... -0.008739639, 0.051767252]
```
