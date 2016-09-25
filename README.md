                                                          PING-PONG OS
                                          Leonardo W Pereira & Lucas Zimmermann Cordeiro 
                                                            
                                                            
                                                  FRDM-K64F utilizando o KDS
  No arquivo config/config.h, é possível alterar a seguinte configuração do sistema:
  - Língua: - Português                  - Inglês                     - Alemão
  
  basta modificar o #define IDIOMA_ATUAL
 

                                          Install OpenSDAv2 Firmware on FRDM-K64F Board

                                                    (Escolha ou JLink ou MBED)

The FRDM-K64F platform features OpenSDAv2 that offers several options for serial communication, flash programming, and run-control debugging. The Embedded Coder Support Package for Freescale FRDM-K64F Board supports the boards that are loaded with two variants of OpenSDAv2 firmware, mbed-firmware and the JLink Segger firmware. This section describes the steps to update the board with mbed-frimware or the segger firmware.

Install JLink Segger Firmware for Freescale FRDM-K64F Board
Download the JLink_OpenSDA_V2_2015-10-13.zip from the link: https://www.segger.com/admin/uploads/userfiles/file/J-Link/OpenSDA/JLink_OpenSDA_V2_2015-10-13.zip.
The LED blinks on the board indicating that the board is now in bootloader mode. Release the Reset button.
Hold down the Reset button on the FRDM-K64F board and connect a USB cable from your computer to the OpenSDA mini-B USB connector of the FRDM-K64F board.
Open Windows Explorer and locate the BOOTLOADER drive.
Copy the file JLink_OpenSDA_V2_2015-10-13.bin from the folder in which you unzipped JLink_OpenSDA_V2_2015-10-13.zip to the BOOTLOADER drive on your computer.
To power cycle your board, unplug your board from the computer, and then plug it back in to the computer.
Once the board is plugged into the computer. You can see the JLINK drive in the windows explorer.
Install mbed Firmware for Freescale FRDM-K64F Board
The FRDM-K64F board comes with the mbed CMSIS-DAP firmware installed by default. It appears as a removable storage drive with a volume label of MBED.

If the volume label MBED does not appear or to upgarde your board with mbed firmware, follow the steps below.

Download the latest mbed interface upgrade file for the FRDM-K64F from the link: https://developer.mbed.org/handbook/Firmware-FRDM-K64F.
Press the Reset button on the FRDM-K64F board and connect a USB cable from your computer to the OpenSDA mini-B USB connector of the FRDM-K64F board.
The LED blinks on the board indicating that the board is in the bootloader mode. Release the Reset button.
Open Windows Explorer and locate the BOOTLOADER drive.
Copy the file 0226_k20dx128_k64f_0x5000.bin from the folder in which you downloaded to the BOOTLOADER drive on your computer.
To power cycle your board, unplug your board from the computer, and plug it back in to the computer.
Once the board is plugged into the computer, you can see the MED drive in the windows explorer.



                                                            CUIDADOS
  
  Na hora de importar o projeto, é imprescindível verificar se todos os PATHs inclusos estão corretos de acordo com a sua máquina!
  Para isso vá em: Project/Properties/C/C++ Build/Settings
  - Cross ARM C Compiler/Includes

E caso necessário, modifique o caminho dos arquivos

                                                            Para DEBUG
    
  Pode-se utilizar o PUTTY (disponível também no projeto aqui no GIT) no modo serial, configurando a porta de acordo com a sua conexão serial.
  Normalmente é a porta COMx da entrada SERIAL.
