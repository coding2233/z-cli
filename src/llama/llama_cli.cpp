#include "llama_cli.h"
// #include "llama.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

// static void print_usage(int, char ** argv) {
//     printf("\nexample usage:\n");
//     printf("\n    %s -m model.gguf [-n n_predict] [-ngl n_gpu_layers] [prompt]\n", argv[0]);
//     printf("\n");
// }


bool LlamaCli::Run(std::vector<std::string> args) 
{
    // path to the model gguf file
    std::string model_path;
    // prompt to generate text from
    std::string prompt = "Hello my name is ";
    for (size_t i = 0; i < args.size(); i++)
    {
        if (args[i] == "-m")
        {
            model_path = args[i+1];
            i++;
        }
        else
        {
            prompt += args[i];
        }
    }

    if (model_path.empty()) {
        // print_usage(args, argv);
        return 1;
    }
    
    RunModel(model_path, prompt);

    return true;
}

std::string LlamaCli::GetHelp() 
{
    return "llama help";
}

int LlamaCli::RunModel(std::string model_path, std::string prompt)
{
    // gpt_params params;

    // params.prompt = "Hello my name is";
    // params.n_predict = 32;

    // if (!gpt_params_parse(argc, argv, params, LLAMA_EXAMPLE_COMMON, print_usage)) {
    //     return 1;
    // }

    // gpt_init();

    // // total length of the sequence including the prompt
    // const int n_predict = params.n_predict;

    // // init LLM

    // llama_backend_init();
    // llama_numa_init(params.numa);

    // // initialize the model

    // llama_model_params model_params = llama_model_params_from_gpt_params(params);

    // llama_model * model = llama_load_model_from_file(params.model.c_str(), model_params);

    // if (model == NULL) {
    //     fprintf(stderr , "%s: error: unable to load model\n" , __func__);
    //     return 1;
    // }

    // // initialize the context

    // llama_context_params ctx_params = llama_context_params_from_gpt_params(params);

    // llama_context * ctx = llama_new_context_with_model(model, ctx_params);

    // if (ctx == NULL) {
    //     fprintf(stderr , "%s: error: failed to create the llama_context\n" , __func__);
    //     return 1;
    // }

    // auto sparams = llama_sampler_chain_default_params();

    // sparams.no_perf = false;

    // llama_sampler * smpl = llama_sampler_chain_init(sparams);

    // llama_sampler_chain_add(smpl, llama_sampler_init_greedy());

    // // tokenize the prompt

    // std::vector<llama_token> tokens_list;
    // tokens_list = ::llama_tokenize(ctx, params.prompt, true);

    // const int n_ctx    = llama_n_ctx(ctx);
    // const int n_kv_req = tokens_list.size() + (n_predict - tokens_list.size());

    // LOG("\n");
    // LOG_INF("%s: n_predict = %d, n_ctx = %d, n_kv_req = %d\n", __func__, n_predict, n_ctx, n_kv_req);

    // // make sure the KV cache is big enough to hold all the prompt and generated tokens
    // if (n_kv_req > n_ctx) {
    //     LOG_ERR("%s: error: n_kv_req > n_ctx, the required KV cache size is not big enough\n", __func__);
    //     LOG_ERR("%s:        either reduce n_predict or increase n_ctx\n", __func__);
    //     return 1;
    // }

    // // print the prompt token-by-token

    // LOG("\n");

    // for (auto id : tokens_list) {
    //     LOG("%s", llama_token_to_piece(ctx, id).c_str());
    // }

    // // create a llama_batch with size 512
    // // we use this object to submit token data for decoding

    // llama_batch batch = llama_batch_init(512, 0, 1);

    // // evaluate the initial prompt
    // for (size_t i = 0; i < tokens_list.size(); i++) {
    //     llama_batch_add(batch, tokens_list[i], i, { 0 }, false);
    // }

    // // llama_decode will output logits only for the last token of the prompt
    // batch.logits[batch.n_tokens - 1] = true;

    // if (llama_decode(ctx, batch) != 0) {
    //     LOG("%s: llama_decode() failed\n", __func__);
    //     return 1;
    // }

    // // main loop

    // int n_cur    = batch.n_tokens;
    // int n_decode = 0;

    // const auto t_main_start = ggml_time_us();

    // while (n_cur <= n_predict) {
    //     // sample the next token
    //     {
    //         const llama_token new_token_id = llama_sampler_sample(smpl, ctx, -1);

    //         // is it an end of generation?
    //         if (llama_token_is_eog(model, new_token_id) || n_cur == n_predict) {
    //             LOG("\n");

    //             break;
    //         }

    //         LOG("%s", llama_token_to_piece(ctx, new_token_id).c_str());
    //         fflush(stdout);

    //         // prepare the next batch
    //         llama_batch_clear(batch);

    //         // push this new token for next evaluation
    //         llama_batch_add(batch, new_token_id, n_cur, { 0 }, true);

    //         n_decode += 1;
    //     }

    //     n_cur += 1;

    //     // evaluate the current batch with the transformer model
    //     if (llama_decode(ctx, batch)) {
    //         LOG_ERR("%s : failed to eval, return code %d\n", __func__, 1);
    //         return 1;
    //     }
    // }

    // LOG("\n");

    // const auto t_main_end = ggml_time_us();

    // LOG_INF("%s: decoded %d tokens in %.2f s, speed: %.2f t/s\n",
    //         __func__, n_decode, (t_main_end - t_main_start) / 1000000.0f, n_decode / ((t_main_end - t_main_start) / 1000000.0f));

    // LOG("\n");
    // llama_perf_sampler_print(smpl);
    // llama_perf_context_print(ctx);

    // LOG("\n");

    // llama_batch_free(batch);
    // llama_sampler_free(smpl);
    // llama_free(ctx);
    // llama_free_model(model);

    // llama_backend_free();

    return 0;
}
