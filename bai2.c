#include <stdio.h>
#include <string.h>

struct FlightTicket {
    char pnrCode[15];
    char passengerName[50];
    int ticketClass;
    float baggageWeight;
    float baggageFee;
};

int main() {
    struct FlightTicket danhSachVe[100];
    int soLuong = 0;
    int choice;
    int i, j, found;
    char pnrInput[15];

    do {
        printf("\n=== HE THONG BAN VE VA CHECK-IN MAY BAY ===\n");
        printf("1. Them ve may bay moi\n");
        printf("2. Hien thi danh sach ve\n");
        printf("3. Cap nhat hanh ly theo PNR\n");
        printf("4. Xoa ve theo PNR\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (soLuong >= 100) {
                    printf("Danh sach ve da day, khong the them moi!\n");
                    break;
                }
                
                printf("Nhap ma PNR: ");
                scanf("%s", danhSachVe[soLuong].pnrCode);
                
                while (getchar() != '\n');
                
                printf("Nhap ho ten hanh khach: ");
                fgets(danhSachVe[soLuong].passengerName, sizeof(danhSachVe[soLuong].passengerName), stdin);
                danhSachVe[soLuong].passengerName[strcspn(danhSachVe[soLuong].passengerName, "\n")] = '\0';
                
                printf("Nhap hang ve (1-Eco, 2-Deluxe, 3-Business): ");
                scanf("%d", &danhSachVe[soLuong].ticketClass);
                
                printf("Nhap khoi luong hanh ly (kg): ");
                scanf("%f", &danhSachVe[soLuong].baggageWeight);

                if (danhSachVe[soLuong].ticketClass == 3) {
                    danhSachVe[soLuong].baggageFee = 0.0;
                } else if (danhSachVe[soLuong].ticketClass == 1 || danhSachVe[soLuong].ticketClass == 2) {
                    if (danhSachVe[soLuong].baggageWeight <= 7.0) {
                        danhSachVe[soLuong].baggageFee = 0.0;
                    } else {
                        danhSachVe[soLuong].baggageFee = (danhSachVe[soLuong].baggageWeight - 7.0) * 50000.0;
                    }
                } else {
                    danhSachVe[soLuong].baggageFee = 0.0;
                }

                soLuong++;
                printf("=> Them ve thanh cong! Cuoc phat hanh ly qua can: %.0f VND.\n", danhSachVe[soLuong - 1].baggageFee);
                break;

            case 2:
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("\n========================================================================================\n");
                printf("%-4s | %-10s | %-25s | %-10s | %-14s | %-15s\n", "STT", "Ma PNR", "Ho ten hanh khach", "Hang ve", "Hanh ly (kg)", "Cuoc qua cuoc");
                printf("========================================================================================\n");
                for (i = 0; i < soLuong; i++) {
                    char className[15];
                    if (danhSachVe[i].ticketClass == 1) strcpy(className, "Eco");
                    else if (danhSachVe[i].ticketClass == 2) strcpy(className, "Deluxe");
                    else strcpy(className, "Business");

                    printf("%-4d | %-10s | %-25s | %-10s | %-14.1f | %.0f VND\n", 
                        i + 1, 
                        danhSachVe[i].pnrCode, 
                        danhSachVe[i].passengerName, 
                        className, 
                        danhSachVe[i].baggageWeight, 
                        danhSachVe[i].baggageFee);
                }
                printf("========================================================================================\n");
                break;

            case 3:
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("Nhap ma PNR can cap nhat hanh ly: ");
                scanf("%s", pnrInput);

                found = 0;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                        found = 1;
                        printf("Tim thay hanh khach: %s\n", danhSachVe[i].passengerName);
                        printf("Nhap trong luong hanh ly moi (kg): ");
                        scanf("%f", &danhSachVe[i].baggageWeight);

                        if (danhSachVe[i].ticketClass == 3) {
                            danhSachVe[i].baggageFee = 0.0;
                        } else if (danhSachVe[i].ticketClass == 1 || danhSachVe[i].ticketClass == 2) {
                            if (danhSachVe[i].baggageWeight <= 7.0) {
                                danhSachVe[i].baggageFee = 0.0;
                            } else {
                                danhSachVe[i].baggageFee = (danhSachVe[i].baggageWeight - 7.0) * 50000.0;
                            }
                        }

                        printf("=> Cap nhat thanh cong! Phi hanh ly qua cuoc moi: %.0f VND.\n", danhSachVe[i].baggageFee);
                        break;
                    }
                }

                if (!found) {
                    printf("Khong tim thay ve co ma PNR da nhap!\n");
                }
                break;

            case 4:
                if (soLuong == 0) {
                    printf("Danh sach ve dang rong!\n");
                    break;
                }

                printf("Nhap ma PNR can xoa: ");
                scanf("%s", pnrInput);

                found = 0;
                for (i = 0; i < soLuong; i++) {
                    if (strcmp(danhSachVe[i].pnrCode, pnrInput) == 0) {
                        found = 1;
                        for (j = i; j < soLuong - 1; j++) {
                            danhSachVe[j] = danhSachVe[j + 1];
                        }
                        soLuong--;
                        printf("=> Da xoa thanh cong ve co ma PNR: %s ra khoi he thong.\n", pnrInput);
                        break;
                    }
                }

                if (!found) {
                    printf("Khong tim thay ve co ma PNR da nhap!\n");
                }
                break;

            case 5:
                printf("Cam ơn ban da su dung he thong. Tam biet!\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long chon lai tu 1 den 5!\n");
        }
    } while (choice != 5);

    return 0;
}