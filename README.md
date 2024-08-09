# C8380-LLaMA-on-WoS

1. Download qnn-2.20 from https://softwarecenter.qualcomm.com/#/catalog/item/a0844287-db23-11ed-a260-063166a9270b， choose windows-2.20.0.240223.

2. Install qualcomm_ai_engine_direct.2.20.0.240223.Windows-AnyCPU.exe

3. Copy C:\Qualcomm\AIStack\QNN\2.20.0.240223\lib\hexagon-v73\unsigned\libQnnHtpV73Skel.so to C8380-LLaMA-on-WoS/LLaMA-on-WoS/lib/

4. Copy C:\Qualcomm\AIStack\QNN\2.20.0.240223\lib\hexagon-v73\unsigned\libQnnHtpV73Skel.so to C8380-LLaMA-on-WoS/LLaMA-on-WoS/bin/

5. Copy C:\Qualcomm\AIStack\QNN\2.20.0.240223\lib\aarch64-windows-msvc\\* to C8380-LLaMA-on-WoS/LLaMA-on-WoS/lib/

6. Copy C:\Qualcomm\AIStack\QNN\2.20.0.240223\lib\aarch64-windows-msvc\\* to C8380-LLaMA-on-WoS/LLaMA-on-WoS/bin/

7. Download 

   1.  https://github.com/Flamingo2023/C8380-LLaMA-on-WoS/releases/download/release-1.0/8m_v73_qc_hf_llama_7b_1_of_4.serialized.bin
   2. https://github.com/Flamingo2023/C8380-LLaMA-on-WoS/releases/download/release-1.0/8m_v73_qc_hf_llama_7b_2_of_4.serialized.bin
   3. https://github.com/Flamingo2023/C8380-LLaMA-on-WoS/releases/download/release-1.0/8m_v73_qc_hf_llama_7b_3_of_4.serialized.bin
   4. https://github.com/Flamingo2023/C8380-LLaMA-on-WoS/releases/download/release-1.0/8m_v73_qc_hf_llama_7b_4_of_4.serialized.bin

   and copy model files to LLaMA-on-WoS/models/llama-v2/7B-FT/
